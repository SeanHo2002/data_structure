#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#define BUF_SIZE 1024
int main(int argc, char* argv[]) {
	int sockfd;//���ݳs�u��socket_id
	int new_fd;//�����s�u��ssocket_id
	struct sockaddr_in my_addr;//local_server_ip_port
	struct sockaddr_in client_addr;//client_ip_port
	char buf[BUF_SIZE];
	int retVal;
	int sin_size;
	WSADATA wsd;
	retVal = WSAStartup(MAKEWORD(2, 2), &wsd);//�Ұ�WSADATA
	if (retVal!=0) {//�ҰʬO�_���\
		printf("winsock startup failed!\n");//��ܿ��~�T��
		return -1;//�{������
	}
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//�إ�socket�N�X
	if (sockfd==-1) {//�إ߬O�_���\
		printf("socket() failed!\n");//��ܿ��~�T��
		WSACleanup();//����WSADATA
		return -1;//�{������
	}
	my_addr.sin_family = AF_INET;//ipv4
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);//�Ҧ����d
	my_addr.sin_port = htons((short)6666);//port ******���I���q(a)******
	sin_size = sizeof(my_addr);//my_addr��size
	retVal = bind(sockfd, (struct sockaddr*)&my_addr, sin_size);//�j�wmy_addr��sockfd
	if (retVal == -1) {//�j�w�O�_���\
		printf("bind failed!\n");//��ܿ��~�T��
		closesocket(sockfd);//�����s�u
		WSACleanup();//����WSADATA
		return -1;//�{������
	}
	retVal = listen(sockfd, 10);//�Ұʺ�ť(�̦h����10�ӳs�u)
	if (retVal == -1) {//�Ұʺ�ť�O�_���\
		printf("listening failed!\n");//��ܿ��~�T��
		closesocket(sockfd);//�����s�u
		WSACleanup();//����WSADATA
		return -1;//�{������
	}
	printf("server is running\n");//���A���i�B��
	new_fd = accept(sockfd, (struct sockaddr*)&client_addr, &sin_size);//�T�w�s�u
	if (new_fd == -1) {//�s�u���q�L
		printf("accepting failed!\n");//��ܿ��~�T��
		//continue;//�~�򱵦��U�@�ӳs�u
	}
	memset(buf, 0, BUF_SIZE);
	retVal = recv(new_fd, buf, BUF_SIZE, 0);//�����T��
	if (retVal <= 0) {//�����O�_���\
		printf("recv error!close connection\n");//��ܿ��~�T��
		closesocket(new_fd);//�����s�u
		return -1;//�{������
	}
	buf[retVal] = '\0';//�̫ᬰ��
	printf("r:%s", buf);//�L�X���e
	printf("\n", buf);//�L�X���e
	strcpy(buf, "Hello! This is a word count service.");//�]�w�ǰe���e ******���I���q(b)******
	retVal = send(new_fd, buf, strlen(buf), 0); //�ǰe�q�Ȥ�ݦ��쪺�T��
	if (retVal == SOCKET_ERROR) {//�ǰe�O�_���\
		printf("send failed!\n");//��ܿ��~�T��
		closesocket(new_fd);//�����s�u
		WSACleanup();//����WSADATA
		return -1;//�{������
	}
	while (true) {//���򱵦��T��
		memset(buf, 0, BUF_SIZE);
		retVal = recv(new_fd, buf, BUF_SIZE, 0);//�����T��
		if (retVal <= 0) {//�����O�_���\
			printf("recv error!close connection\n");//��ܿ��~�T��
			closesocket(new_fd);//�����s�u
			return -1;//�{������
		}
		buf[retVal] = '\0';//�̫ᬰ��
		printf("r:%s", buf);//�L�X���e
		char carry[BUF_SIZE];//�إߧ֨��A�P�_�O�_����
		ZeroMemory(carry, BUF_SIZE);
		strcpy(carry, buf);//�]�w�֨�
		printf("\n", buf);//�L�X���e
		int time = strlen(buf);//�]�w�ǰe���e���r����� ******���I���q(c)******
		_itoa(time,buf,10);////�]�w�ǰe���e���r�����   ******���I���q(c)******
		retVal = send(new_fd, buf, strlen(buf), 0); //�ǰe�T��
		if (retVal == SOCKET_ERROR) {//�ǰe�O�_���\
			printf("send failed!\n");//��ܿ��~�T��
			closesocket(new_fd);//�����s�u
			WSACleanup();//����WSADATA
			return -1;//�{������
		}
		if (carry[0] == 'E' && carry[1] == 'N' && carry[2] == 'D') // �p�G��J"END"�{������
			return -1;//�{������
	}
	return 0;
}