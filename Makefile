CC = g++ 
CC_FLAGS = -std=c++17 -pthread
OUT = ./out
BUILD = ${OUT}/build

all: server client
	
server: argsWrapper socket clientStorageManager
	${CC} ${CC_FLAGS} server/main.cpp server/Server.cpp ${BUILD}/argsWrapper.o ${BUILD}/socket.o ${BUILD}/clientStorageManager.o -o ${OUT}/run_server

client: argsWrapper socket
	${CC} ${CC_FLAGS} client/main.cpp client/Client.cpp ${BUILD}/argsWrapper.o ${BUILD}/socket.o -o ${OUT}/run_client

clientStorageManager: acceptedClient clientStorage
	${CC} ${CC_FLAGS} -c server/clientStorage/ClientStorageManager.cpp ${BUILD}/acceptedClient.o ${BUILD}/clientStorage.o -o ${BUILD}/clientStorageManager.o 

clientStorage: acceptedClient
	${CC} ${CC_FLAGS} -c server/clientStorage/ClientStorage.cpp ${BUILD}/acceptedClient.o -o ${BUILD}/clientStorage.o 

acceptedClient: outDir server/clientStorage/AcceptedClient.cpp
	${CC} ${CC_FLAGS} -c server/clientStorage/AcceptedClient.cpp -o ${BUILD}/acceptedClient.o 

socket: outDir common/socket/Socket.cpp
	${CC} ${CC_FLAGS} -c common/socket/Socket.cpp -o ${BUILD}/socket.o

argsWrapper: outDir argsWrapper/ArgsWrapper.cpp
	${CC} ${CC_FLAGS} -c argsWrapper/ArgsWrapper.cpp -o ${BUILD}/argsWrapper.o

outDir:
	mkdir -p ${OUT} ${BUILD}

clean:
	rm -rf ${OUT}