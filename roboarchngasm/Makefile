CC = gcc
LDFLAGS =
CFLAGS = -Wall -Ofast -fstrict-aliasing -march=native
OBJECTS = roboarchngasm.o stringlib.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

roboarchngasm: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

debug:	CFLAGS= -Wall -O0 -g  -fstrict-aliasing -march=native
debug: 	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o roboarchngasm-$@ $(LDFLAGS)


clean:
	@echo cleaning oop
	@rm -f $(OBJECTS)
purge:
	@echo purging oop
	@rm -f $(OBJECTS)
	@rm -f roboarchngasm
	@rm -f roboarchngasm-debug
