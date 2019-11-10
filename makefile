CC  = gcc
INCL = -I./include

patriconf: patriconf.c shared_mutex.a
	$(CC) $^ -shared -fpic -o libpatriconf.so $(INCL) -lrt

test: test_patriconf.c patriconf.c
	$(CC) test_patriconf.c -Wall -g -o test -lpatriconf -L. -lpthread $(INCL) 

shared_mutex.a:
mutex: ./shared_mutex/shared_mutex.c
	$(CC) $< -c -o shared_mutex.a -lrt -lpthread
	
shared_mutex: ./shared_mutex/shared_mutex.c
	$(CC) $< -shared -fpic -o libshared_mutex.so -lrt -lpthread 

%.o: %.c
	$(CC)  -Wall -g -c $<

.PHONY: clean
clean:
	rm -rf *.so
	rm -rf *.o
	rm -f test

