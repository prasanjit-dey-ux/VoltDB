CC = g++
CFLAGS = -Wall -std=c++11

all: server

server: main.o tcp_server.o resp_parser.o storage_engine.o
	$(CC) $(CFLAGS) -o server main.o tcp_server.o resp_parser.o storage_engine.o

main.o: main.cpp tcp_server.h
	$(CC) $(CFLAGS) -c main.cpp

tcp_server.o: tcp_server.cpp tcp_server.h storage_engine.h resp_parser.h
	$(CC) $(CFLAGS) -c tcp_server.cpp

resp_parser.o: resp_parser.cpp resp_parser.h
	$(CC) $(CFLAGS) -c resp_parser.cpp

storage_engine.o: storage_engine.cpp storage_engine.h
	$(CC) $(CFLAGS) -c storage_engine.cpp

clean:
	rm -f *.o server

