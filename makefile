all: print_server

print_server: main.cpp Logger.cpp QueueManager.cpp Producer.cpp Consumer.cpp TCPManager.cpp
	@g++ -std=c++17 -g -I. -o print_server main.cpp Logger.cpp QueueManager.cpp Producer.cpp Consumer.cpp TCPManager.cpp -lstdc++fs

clean:
	rm -f print_server