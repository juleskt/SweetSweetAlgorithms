# in EC327, we use the ${GCC} compiler
# therefore, we define the GCC variable
GCC = g++ -std=c++0x -O2 -g

test: ClientSocket.o Socket.o lmao.o
	${GCC} ClientSocket.o Socket.o lmao.o -o test
	
ClientSocket.o: ClientSocket.cpp
	${GCC} -c ClientSocket.cpp -o ClientSocket.o

Socket.o: Socket.cpp 
	${GCC} -c Socket.cpp -o Socket.o

lmao.o: simple_client_main.cpp
	${GCC} -c simple_client_main.cpp -o lmao.o

clean:
	rm lmao.o Socket.o ClientSocket.o 
