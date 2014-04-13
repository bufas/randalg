CC=clang++
CFLAGS=-g -Wall -std=c++11 -stdlib=libc++

test: find.cpp
	$(CC) $(CFLAGS) -o find find.cpp

.PHONY: clean
clean:
	$(RM) find
	$(RM) -r find.dSYM