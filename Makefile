CFLAGS=-Wall -g -Ideps/yodawg/src
INSTALL_PATH=/usr/local/bin

all: yodawg
	$(CC) $(CFLAGS) src/main.c -o build/yodawgd build/yodawg.o

yodawg:
	$(CC) $(CFLAGS) -c deps/yodawg/src/yodawg.c -o build/yodawg.o

install:
	cp build/yodawgd $(INSTALL_PATH)/yodawgd

uninstall:
	rm -rf $(INSTALL_PATH)/yodawgd

clean:
	rm -rf build/*
