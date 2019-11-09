CC      = gcc

patriconf: patriconf.c 
	$(CC) $< -shared -fpic -o libpatriconf.so	

test: test_patriconf.c patriconf.c
	$(CC) test_patriconf.c -Wall -g -o test -lpatriconf -L. -lpthread


%.o: %.c
	$(CC)  -Wall -g -c $<

.PHONY: clean
clean:
	rm -rf *.so
	rm -rf *.o
	rm -f test
