#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcpy which is essential for copy

#define DEBUGMODE

#define TRUE 1
#define FALSE 0


unsigned int memsize = 65536;
unsigned char * mem = 0;




void doop(const int op, int a, int b, int c){
	#ifdef DEBUGMODE
		int oga = ((int*)mem)[a];
		int ogb = ((int*)mem)[b];
	#endif
	switch(op){
		case 0://no-op
//			memcpy(((int*)mem) + a, ((int*)mem) + b, ((int *)mem) + c);
		break;
		case 1:	//add
			((int*)mem)[c] = ((int*)mem)[a] + ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i + %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 2:	//sub
			((int*)mem)[c] = ((int*)mem)[a] - ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i - %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 3:	//mult
			((int*)mem)[c] = ((int*)mem)[a] * ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i * %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 4:	//div
			((int*)mem)[c] = ((int*)mem)[a] / ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i / %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 5:	//mod
			((int*)mem)[c] = ((int*)mem)[a] % ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i % %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 6:	//and
			((int*)mem)[c] = ((int*)mem)[a] & ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i & %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 7:	//or
			((int*)mem)[c] = ((int*)mem)[a] | ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i | %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 8:	//xor
			((int*)mem)[c] = ((int*)mem)[a] ^ ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i ^ %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 9:	//not
			((int*)mem)[c] = ~((int*)mem)[a];
			#ifdef DEBUGMODE
				printf("\t%i = ~%i\n", ((int*)mem)[c], oga);
			#endif
		break;
		case 10://bnot
			((int*)mem)[c] = !((int*)mem)[a];
			#ifdef DEBUGMODE
				printf("\t%i = !%i\n", ((int*)mem)[c], oga);
			#endif
		break;
		case 11://sl
			((int*)mem)[c] = ((int*)mem)[a] << ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i << %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 12://sr
			((int*)mem)[c] = ((unsigned int*)mem)[a] >> ((int*)mem)[b]; //the unsigned tricks c into logical shift?
			#ifdef DEBUGMODE
				printf("\t%i = %i >>l %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 13://sa
			((int*)mem)[c] = ((int*)mem)[a] >> ((int*)mem)[b];
			#ifdef DEBUGMODE
				printf("\t%i = %i >>a %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 14://tg
			((int*)mem)[c] = (((int*)mem)[a] > ((int*)mem)[b]);
			#ifdef DEBUGMODE
				printf("\t%i = %i > %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		case 15://te
			((int*)mem)[c] = (((int*)mem)[a] == ((int*)mem)[b]);
			#ifdef DEBUGMODE
				printf("\t%i = %i == %i\n", ((int*)mem)[c], oga, ogb);
			#endif
		break;
		default: break;//noop
	}
			#ifdef DEBUGMODE
				if(op < 16 && op > 0) printf("\twriting %i to 0x%04x\n", ((int*)mem)[c], c);
				else { printf("\tNop!");}
			#endif

}

void executionloop(void){
	int ip;
	for(;(ip = ((int*)mem)[0]); ((int*)mem)[0]+=4){
		int op = ((int*)mem)[ip];
		int a = ((int*)mem)[ip+1];
		int b = ((int*)mem)[ip+2];
		int c = ((int*)mem)[ip+3];
		#ifdef DEBUGMODE
			printf("%i with opcode %i, %i, %i, %i\n", ip, op, a, b, c);
		#endif

		doop(op, a, b, c);
	}
}
int main(int argc, char ** argv){
	//grab input file
	char * filename = argc > 1 ? argv[1] : "./program.bin";
	FILE *f = fopen(filename, "rb");
	if(!f){
		printf("File %s not found\n", filename);
		return TRUE;
	}
	fseek(f, 0, SEEK_END);
	int filesize = ftell(f);
	rewind(f);
	memsize = (filesize + memsize-1) & ~(memsize -1);
	if(argc > 2){
		int presize = atoi(argv[2]);
		if(presize < filesize) printf("Memsize %i too small for a %i file, setting to %i\n", presize, filesize, memsize);
		else memsize = presize;
	}
	mem = malloc(memsize);
	fread(mem, 1, filesize, f);
	if(f)fclose(f); f = 0;
	memset(mem + filesize, 0, memsize - filesize);
	executionloop();
	//dump output
	if(argc > 3) f = fopen(argv[3], "wb");
	if(f){
		//find end of mem
		int i;
		for(i = (memsize-1)/4; i >= 0 && !((int*)mem)[i]; i--);
		i++;
		if(i){
			printf("dumping %i bytes to file %s\n", i*4, argv[3]);
			fwrite(mem, i*4, 1, f);
		} else printf("no bytes to write\n");
	}
	if(mem) free(mem); mem = 0;
	return FALSE;
}
