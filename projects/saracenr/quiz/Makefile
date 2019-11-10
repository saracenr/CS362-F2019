CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme.o: testme.c
	gcc -c testme.c -g  $(CFLAGS)

testme: testme.o
	gcc -o testme testme.o -g $(CFLAGS)

runtests: testme
	testme

clean:
	rm -f *.gcov *.gcda *.gcno *.so testme testme.o