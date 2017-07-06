FLAGS = -O
CC = g++ #clang++
myapp: main.o graph.o node.o LRU.o jsoncpp.o
	$(CC) $(CFLAGS) -o myapp main.o graph.o node.o LRU.o jsoncpp.o
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 
graph.o: graph.cpp
	$(CC) $(CFLAGS) -c graph.cpp
node.o: node.cpp
	$(CC) $(CFLAGS) -c node.cpp
LRU.o: LRU.cpp
	$(CC) $(CFLAGS) -c LRU.cpp
jsoncpp.o: jsoncpp.cpp
	$(CC) $(CFLAGS) -c jsoncpp.cpp

clean:
	rm -f myapp *.o 
