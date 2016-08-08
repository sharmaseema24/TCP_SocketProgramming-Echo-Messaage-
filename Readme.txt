1. Compile server source file: 
	gcc TCP_Server.c -o tcpServer
2. Compile client source file: 
	gcc TCP_Client.c -o tcpClient
3. Run Server on Port 8095: 
	./tcpServer 8095

4. Check server is running using another terminal: 
	netstat -atp

	list should display TCP listening port (e.g. 8093) as below:
	Proto  Recv-Q    Send-Q    Local Addr   Foreign Addr      State       PID/Program name
	tcp      0           0        *:8095        *:*           LISTEN       3798/tcpServer

5. Run Client with localhost ip "127.0.0.1" and remote server Port "8095":
	./tcpClient 127.0.0.1 8905

6. Test Client Server Communication (Echo Messaging):
   - send message "Hello World!!!" from client to server
   - Message "Hello World!!!" should be dispalyed on terminal running server
   - Same Message "Hello World!!!" should be received back on Client terminal

	
