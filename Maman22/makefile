myset: myset.o handlers.o set.o misc.o  misc.o
	gcc -ansi -Wall -pedantic set.o handlers.o misc.o myset.o -o myset
set.o: set.c set.h
	gcc -c -ansi -Wall -pedantic set.c -o set.o
misc.o: misc.c misc.h
	gcc -c -ansi -Wall -pedantic misc.c -o misc.o
handlers.o: set.o misc.o handlers.c handlers.h
	gcc -c -ansi -Wall -pedantic handlers.c -o handlers.o
myset.o: myset.c handlers.h
	gcc -c -ansi -Wall -pedantic myset.c -o myset.o
