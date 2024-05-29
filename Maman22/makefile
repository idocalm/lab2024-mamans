myset: functions.o set.o set.h
	gcc -ansi -Wall -pedantic set.c myset.c -o myset
functions.o: functions.c set.h
	gcc -c -ansi -Wall -pedantic functions.c -o functions.o
set.o: functions.o set.c set.h
	gcc -c -ansi -Wall -pedantic set.c -o set.o
