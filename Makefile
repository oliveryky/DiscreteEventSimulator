CPPFLAGS= -std=c++17
CC=clang++

all: simulator

simulator: main.o main.cpp Environment.h Event.h EventQueue.h SuperMarket.h Bank.h
	$(CC) $(CPPFLAGS) -o simulator main.o

clean:
	-rm *.o simulator
