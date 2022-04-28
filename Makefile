CC = g++ 
CC_FLAGS = -std=c++17 -pthread
OUT = ./out
BUILD = ${OUT}/build

all: server client

client: outDir client.o client.main.o socket argsWrapper
	${CC} ${CC_FLAGS} ${BUILD}/client.main.o ${BUILD}/client.o ${BUILD}/socket.o ${BUILD}/argsWrapper.o -o ${OUT}/client

server: outDir server.o server.main.o clientStorageManager socket argsWrapper
	${CC} ${CC_FLAGS} ${BUILD}/server.main.o ${BUILD}/server.o ${BUILD}/clientStorageManager.o ${BUILD}/clientStorage.o ${BUILD}/acceptedClient.o ${BUILD}/socket.o ${BUILD}/argsWrapper.o -o ${OUT}/server

client.main.o:
	${CC} ${CC_FLAGS} -c client/main.cpp -o ${BUILD}/client.main.o

client.o:
	${CC} ${CC_FLAGS} -c client/Client.cpp -o ${BUILD}/client.o

server.main.o:
	${CC} ${CC_FLAGS} -c server/main.cpp -o ${BUILD}/server.main.o

server.o: 
	${CC} ${CC_FLAGS} -c server/Server.cpp -o ${BUILD}/server.o

clientStorageManager: clientStorage
	${CC} ${CC_FLAGS} -c server/clientStorage/ClientStorageManager.cpp -o ${BUILD}/clientStorageManager.o 

clientStorage: acceptedClient
	${CC} ${CC_FLAGS} -c server/clientStorage/ClientStorage.cpp -o ${BUILD}/clientStorage.o 

acceptedClient: 
	${CC} ${CC_FLAGS} -c server/clientStorage/AcceptedClient.cpp -o ${BUILD}/acceptedClient.o 

socket: common/socket/Socket.cpp
	${CC} ${CC_FLAGS} -c common/socket/Socket.cpp -o ${BUILD}/socket.o

argsWrapper: argsWrapper/ArgsWrapper.cpp
	${CC} ${CC_FLAGS} -c argsWrapper/ArgsWrapper.cpp -o ${BUILD}/argsWrapper.o

outDir:
	mkdir -p ${OUT} ${BUILD}

clean:
	rm -rf ${OUT}