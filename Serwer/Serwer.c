// Serwer.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <stdio.h>

typedef SOCKET SOCKSTR;
#define PORT 4325
#define LOCAL "127.0.0.1"

void error(char *msg) {
	perror(msg);
	exit(0);
}



int main()
{
	int length, fromlen,fromSlen, n, result;
	SOCKSTR sock,fromsock,newCon;
	struct sockaddr_in server;
	struct sockaddr_in from;
	struct sockaddr_in fromS;
	char buf[1024];
#if _WIN32
	WSADATA wsaData;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		error("WSAStartup failed\n");
		return 1;
	}
#endif

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		error("error occured while opening socket.\n");
	}

	fromsock = socket(AF_INET, SOCK_STREAM, 0);
	if (fromsock < 0) {
		error("error occured while opening socket.\n");
	}

	length = sizeof(server);
	memset(&server, '\0', length);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htons(INADDR_ANY);
	server.sin_port = htons(PORT);

	result=bind(sock, (struct sockaddr *)&server, length);
	if (result < 0) {
		error("error occured while binding socket.\n");
	}

	listen(sock, SOMAXCONN);


	fromlen = sizeof(struct sockaddr_in);
	memset(&from, '\0', fromlen);
	from.sin_family = AF_INET;
	from.sin_addr.s_addr = inet_addr(LOCAL);
	from.sin_port = htons(PORT);

	result = connect(fromsock, (struct sockaddr *)&from, fromlen);

	fromSlen = sizeof(struct sockaddr_in);
	newCon = accept(sock, (SOCKADDR*)&fromS, &fromSlen);

	while (1) {
		
		sprintf(&buf, "XDDDDDD");
		
		n = sendto(fromsock, buf, 17, 0, NULL, NULL);

		if (n < 0) {
			error("error occured while sending.\n");
		}

		n = recvfrom(newCon, buf, 1024, 0,NULL,NULL);
		result=WSAGetLastError();
		if (n < 0) {
			error("recvfrom");
		}

		printf("recieved a datagram: %s\n",buf);
		Sleep(1000);

	}
	return 0;

}

