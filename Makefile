CFLAGS=-Wall -g -Ideps/yodawg/src

all: yodawg
	$(CC) $(CFLAGS) src/main.c -o fillitin build/yodawg.o

yodawg:
	$(CC) $(CFLAGS) -c deps/yodawg/src/yodawg.c -o build/yodawg.o

clean:
	rm -rf build/* fillitin
