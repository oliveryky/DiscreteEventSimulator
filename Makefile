CPPFLAGS= -std=c++17
CC=clang++

all: simulator

simulator: main.o
	$(CC) $(CPPFLAGS) -o $@ $^

clean:
	-rm *.o simulator
