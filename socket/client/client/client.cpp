#include "stdafx.h"
#include <winsock.h>
#include <cstdio>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>
//#include <winsock.h>
SOCKET s;
bool ConnectToHost(int PortNo, char* IPAddress)
{
	WSADATA wsadata;
	
	int error = WSAStartup(0x0202, &wsadata);

	if (error)
	{
		return false;
	}

	if (wsadata.wVersion != 0x0202)
	{
		WSACleanup();
		return false;
	}

	SOCKADDR_IN target;

	target.sin_family = AF_INET;
	target.sin_port = htons(PortNo);
	target.sin_addr.s_addr = inet_addr(IPAddress);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		return false;
	}

	if (connect(s, (SOCKADDR*)&target, sizeof(target)) == SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		return true;
	}
}



void CloseConnection()
{
	if (s)
		closesocket(s);
	WSACleanup();
}


void main()
{
	if (ConnectToHost(5858, "127.0.0.1"))
	{
		while (true)
		{
			char sendBuf[1024];//发送至客户端的字符串
			char recvBuf[1024];//接受客户端返回的字符串

			std::cout << "输入发送信息：";
			std::cin >> sendBuf;

			int b = send(s, sendBuf, strlen(sendBuf) + 1, 0);

			if (b<0)
			{
				std::cout << "发送信息失败";
				char a;
				std::cin >> a;
				break;
			}

			b = recv(s, recvBuf, 1024, 0);
			if (b<0)
			{
				std::cout << "接收信息失败";
				char a;
				std::cin >> a;
				break;
			}			
			std::cout << "服务端信息：" << recvBuf << std::endl;
		}
		

		//char message[20] = "HelloSocket!";
		//send(s, message, strlen(message) + 1, 0);
		CloseConnection();
	}
	else
	{
		std::cout << "Connect failed";
		char a;
		std::cin >> a;
	}
}