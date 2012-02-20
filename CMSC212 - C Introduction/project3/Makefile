#%=wildcard
#$^=all dependencies
#$@=target
#$<=first dependence only
#www.gnu.org/software/make/manual

CC= gcc
CFLAGS= -ansi -pedantic-errors -Werror -Wall


#all : %.x

%.x : %.o string.o node.c
	$(CC) $(CFLAGS) $^ -o $@
	
%.o : %.c node.h string.h
	$(CC) $(CFLAGS) -c $<
	
clean: 
	rm -f public*.x

# or the long way

#public01.x : public01.o interpreter.o assembler.o
#	$(CC) $(CFLAGS) public01.o interpreter.o assembler.o -o public01.x
#	
#public01.o : public01.c interpreter.h assembler.h
#	$(CC) $(CFLAGS) -c public01.c
	
