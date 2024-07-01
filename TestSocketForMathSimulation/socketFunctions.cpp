#include "socketFunctions.h"
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <errno.h>

#ifdef linux
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <netinet/tcp.h>

#endif
#ifdef _UNIX
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <netinet/tcp.h>
#endif
#ifdef __WINDOWS_
#include <winsock2.h>

#endif
#ifdef _WIN32
#include <winsock2.h>

#endif

#pragma comment(lib, "Ws2_32.lib")

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#pragma comment(lib, "Ws2_32.lib")

#define BACKLOG 5 
#include <iostream>
int recv_data(int socket, char* buffer, int length) {
	int total_received = 0;
#ifdef _WINDOWS_
	u_long mode = 1;
	if (ioctlsocket(socket, FIONBIO, &mode) != 0) {
		std::cerr << "ioctlsocket failed" << std::endl;
		closesocket(socket);
		WSACleanup();
		return 1;
	}
#endif
	while (total_received < length) {

		int bytes_received = recv(socket, buffer + total_received, length - total_received, 0);
		if (bytes_received == -1) {
			// 接收发生错误
			int error_code = WSAGetLastError();
			if (error_code == WSAEWOULDBLOCK || error_code == WSAEINTR) {
				// 当前没有数据可读，继续等待
				continue;
			}
			else {
				// 其他错误，返回错误码
				return -1;
			}
		}
		else if (bytes_received == 0) {
			// 对端关闭连接
			return 0;
		}

		// 更新已接收字节数
		total_received += bytes_received;
	}

	return total_received;
}
int send_frame(int socket, char *d_p, int length)
{
	int sended = 0;
	while (true)
	{
		int sendedLength = send(socket, d_p + sended, length-sended , 0);
		if (sendedLength <= 0)
		{
			return sendedLength;
		}
		sended += sendedLength;
		if (sended == length)
			return sended;
		//if (sendedLength == -1)
		//{
		//	std::cout << "connect closed" << std::endl;
		//	return;
		//}
	}
}

void init_socket()
{
#ifdef __WINDOWS_
	WORD versionRequired;
	WSADATA wsadata;
	versionRequired = MAKEWORD(2, 2);
	WSAStartup(versionRequired, &wsadata);
#endif
#ifdef _WIN32
	WORD versionRequired;
	WSADATA wsadata;
	versionRequired = MAKEWORD(2, 2);
	WSAStartup(versionRequired, &wsadata);

#endif
}

int create_socket()
{
	int sockfd;
	int on,ret;
	
	
	
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//ret = setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));
	int nodelay = 1;
	setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (const char*)&nodelay, sizeof(nodelay));
	
	if (sockfd == INVALID_SOCKET)
	{
		perror("socket create failed");
		return -1;
	}

	return sockfd;
}

int bind_listen(int sockfd, int port)
{
	int new_fd;

	struct sockaddr_in my_addr;


	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero), 0, 8);

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == SOCKET_ERROR)
	{
		printf("bind failed!");
		return -1;
	}

	if (listen(sockfd, BACKLOG) == SOCKET_ERROR)
	{
		printf("listen failed");
		return -1;
	}
	return 0;
	
}

int accept_client(int sockfd)
{
	int new_fd;
	int sin_size = sizeof(struct sockaddr_in);

	struct sockaddr_in their_addr;
	printf("waiting for connect\n");
#ifdef linux
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&sin_size);
#endif
#ifdef _UNIX
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&sin_size);
#endif
#ifdef __WINDOWS_
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
#endif
#ifdef _WIN32
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
#endif
	printf("connected\n");

	return new_fd;
}

int CloseSocket(int sockfd)
{
#ifdef linux
	if (close(sockfd) == 0) {
		std::cout << "Socket closed successfully\n";
	}
	else {
		std::cerr << "Error closing socket\n";
		return 1;
	}
#endif
#ifdef _WINDOWS_
	if (closesocket(sockfd) == 0) {
		std::cout << "Socket closed successfully\n";
	}
	else {
		std::cerr << "Error closing socket\n";
		return 1;
	}
#endif
	return 0;
}