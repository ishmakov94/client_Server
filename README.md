# client_Server

Build app:

make        - build all
make client - build client
make server - build server
make clean  - remove build directory

Build directory is ./out

Run app:

./out/client [proto] [server_ip] [port]
[proto]
	-t - TCP
	-u - UDP
[server_ip] 
	-i (default 127.0.0.1) Note: sould be formated X.X.X.X, where  0 <= X <= 255 (default 127.0.0.1)
[port]
	-p (default 1024) Note: sould be mode than 1024 and less than 65535

./out/server [portTcp] [portUdp]
[portTcp]
	-tcp-port (default 1024) Note: sould be more than 1024 and less than 65535 and is not equal Udp port
[portUdp]
	-udp-port (default 1025) Note: sould be more than 1024 and less than 65535 and is not equal Tcp port
