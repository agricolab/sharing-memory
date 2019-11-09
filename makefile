CC      = gcc

patriconf: patriconf.c 
	$(CC) $< -shared -fpic -o libpatconf.so	

%.o: %.c
	$(CC)  -Wall -g -c $<

.PHONY: clean
clean:
	rm -rf *.so
	rm -rf *.o
