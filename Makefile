CC = gcc
LDFLAGS =
CFLAGS = -Wall -Ofast -fstrict-aliasing -march=native
OBJECTS = roboarchngvm.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

roboarchngvm: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

debug:	CFLAGS= -Wall -O0 -g  -fstrict-aliasing -march=native
debug: 	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o roboarchngvm-$@ $(LDFLAGS)


clean:
	@echo cleaning oop
	@rm -f $(OBJECTS)
purge:
	@echo purging oop
	@rm -f $(OBJECTS)
	@rm -f roboarchngvm
	@rm -f roboarchngvm-debug
