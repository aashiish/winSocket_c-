#include "stdafx.h"


#include <Winsock2.h>
#include <cstdio>
#pragma comment(lib,"ws2_32.lib")
#include <iostream>

#include <windows.h>
SOCKET s;
WSADATA w;

bool ListenOnPort(int portNo)
{
	int error = WSAStartup(0x0202, &w);

	if (error)
	{
		return false;
	}

	if (w.wVersion != 0x0202)
	{
		WSACleanup();
		return false;
	}

	SOCKADDR_IN addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(portNo);

	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET)
	{
		return false;
	}

	if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		return false;
	}

	listen(s, SOMAXCONN);

	SOCKET clientSocket;
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	clientSocket = accept(s,(SOCKADDR*)&addrClient,&len);
	char sendBuf[1024];//�������ͻ��˵��ַ���
	char recvBuf[1024];//���ܿͻ��˷��ص��ַ���

	/*recv(clientSocket, recvBuf, 1024, 0);
	std::cout << recvBuf;*/

	while (true)
	{
		int b = recv(clientSocket, recvBuf, 1024, 0);
		if (b<0)
		{
			std::cout << "������Ϣʧ��";
			break;
		}
		std::cout <<"�ͻ�����Ϣ��"<< recvBuf<<std::endl;

		/*std::cout << "����ظ���Ϣ��";
		std::cin >> sendBuf;
		send(clientSocket, sendBuf, 1024, 0);

		if (sendBuf == "q")
		{
			break;
		}*/
		b = send(clientSocket, recvBuf, 1024, 0);
		if (b<0)
		{
			std::cout << "������Ϣʧ��" ;
			break;
		}
		

	}

	closesocket(clientSocket);
	closesocket(s);

	WSACleanup();
	return true;
}

//void showMess()
//{
//
//}

//void CloseConnection()
//{
//	if (s)
//		closesocket(s);
//	WSACleanup();
//}



int main()
{
	if (ListenOnPort(5858))
	{
		//showMess();
	}
}
