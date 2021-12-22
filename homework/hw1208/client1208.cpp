#define _CRT_SECURE_NO_WARNINGS
#define BUF_SIZE 64
#include <winsock.h>
#include <stdio.h>
#include <string.h>
int main(void) {
	WSADATA wsd;
	SOCKET sHost;
	SOCKADDR_IN servAddr;
	char buf[BUF_SIZE];
	int retVal;
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {//�Ұ�WSADATA�çP�_�O�_���\
		printf("WSAStartup failed!\n");//��ܿ��~�T��
		return -1;//�{������
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//�إ�socket�N�X
	if (sHost == INVALID_SOCKET) {//�إ߬O�_���\
		printf("socket creation failed!\n");//��ܿ��~�T��
		WSACleanup();//����WSADATA
		return -1;//�{������
	}
	servAddr.sin_family = AF_INET;//ipv4
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//���A����m
	servAddr.sin_port = htons((short)6666);//�s�uport ******���I���q(a)******
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));//�إ�socket�PservAddr�ҳ]�w��server�s�u
	if (retVal == SOCKET_ERROR) {//�s�u�O�_���\
		printf("connect failed!\n");//��ܿ��~�T��
		closesocket(sHost);//���_�Pserver���s�u
		WSACleanup();//����WSADATA
		return -1;//�{������
	}
	ZeroMemory(buf, BUF_SIZE);
	strcpy(buf, "Hello! server.");//�]�w�ǰe���e
	printf("Sending:%s\n", buf);//��ܶǰe���e
	retVal = send(sHost, buf, strlen(buf), 0); //�ǰe�T��
	if (retVal == SOCKET_ERROR) {//�ǰe�O�_���\
		printf("send failed!\n");//��ܿ��~�T��
		closesocket(sHost);//���_�Pserver���s�u
		WSACleanup();//����WSADATA
		return -1;//�{������
	}
	ZeroMemory(buf, BUF_SIZE);
	retVal = recv(sHost, buf, BUF_SIZE, 0);//�����T��
	if (retVal == SOCKET_ERROR) {//�����O�_���\
		printf("receiv failed!\n");//��ܿ��~�T��
		closesocket(sHost);//���_�Pserver���s�u
		WSACleanup();//����WSADATA
		return -1;//�{������
	}
	buf[retVal] = '\0';//�̫ᬰ��
	printf("received:%s\n", buf);//�L�X���e
	while (true) {//�]�w�ǰe���e ******���I���q(c)******
		char carry[BUF_SIZE];//�إߧ֨��A�P�_�O�_����
		ZeroMemory(buf, BUF_SIZE);
		ZeroMemory(carry, BUF_SIZE);
		scanf("%s", &buf);//Ū����J��
		strcpy(carry, buf);//�]�w�֨�
		printf("Sending:%s\n", buf);//��ܶǰe���e
		retVal = send(sHost, buf, strlen(buf), 0); //�ǰe�T��
		if (retVal == SOCKET_ERROR) {//�ǰe�O�_���\
			printf("send failed!\n");//��ܿ��~�T��
			closesocket(sHost);//���_�Pserver���s�u
			WSACleanup();//����WSADATA
			return -1;//�{������
		}
		ZeroMemory(buf, BUF_SIZE);
		retVal = recv(sHost, buf, BUF_SIZE, 0);//�����T��
		if (retVal == SOCKET_ERROR) {//�����O�_���\
			printf("receiv failed!\n");//��ܿ��~�T��
			closesocket(sHost);//���_�Pserver���s�u
			WSACleanup();//����WSADATA
			return -1;//�{������
		}
		buf[retVal] = '\0';//�̫ᬰ��
		printf("received:%s\n", buf);//�L�X���e
		if (carry[0] == 'E' && carry[1] == 'N' && carry[2] == 'D')//�p�G��J"END"�����s�u
			break;
	}
	getchar();
	closesocket(sHost);//���_�Pserver���s�u
	return 0;
}