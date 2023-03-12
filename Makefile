CC = g++

CompileParms = -c -Wall -std=c++11 -O2

OBJS = main.o

Program: $(OBJS)
	$(CC) $(OBJS) -o scale-identifier

main.o: main.cc main.h
	$(CC) $(CompileParms)  main.cc