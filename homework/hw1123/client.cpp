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
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {//啟動WSADATA並判斷是否成功
		printf("WSAStartup failed!\n");//顯示錯誤訊息
		return -1;//程式結束
	}
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//建立socket代碼
	if (sHost == INVALID_SOCKET) {//建立是否成功
		printf("socket creation failed!\n");//顯示錯誤訊息
		WSACleanup();//關閉WSADATA
		return -1;//程式結束
	}
	servAddr.sin_family = AF_INET;//ipv4
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//伺服器位置
	servAddr.sin_port = htons((short)6666);//連線port ******重點片段(a)******
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));//建立socket與servAddr所設定之server連線
	if (retVal == SOCKET_ERROR) {//連線是否成功
		printf("connect failed!\n");//顯示錯誤訊息
		closesocket(sHost);//中斷與server的連線
		WSACleanup();//關閉WSADATA
		return -1;//程式結束
	}
	ZeroMemory(buf, BUF_SIZE);
	strcpy(buf, "Hello! server.");//設定傳送內容
	printf("Sending:%s\n", buf);//顯示傳送內容
	retVal = send(sHost, buf, strlen(buf), 0); //傳送訊息
	if (retVal == SOCKET_ERROR) {//傳送是否成功
		printf("send failed!\n");//顯示錯誤訊息
		closesocket(sHost);//中斷與server的連線
		WSACleanup();//關閉WSADATA
		return -1;//程式結束
	}
	ZeroMemory(buf, BUF_SIZE);
	retVal = recv(sHost, buf, BUF_SIZE, 0);//接收訊息
	if (retVal == SOCKET_ERROR) {//接收是否成功
		printf("receiv failed!\n");//顯示錯誤訊息
		closesocket(sHost);//中斷與server的連線
		WSACleanup();//關閉WSADATA
		return -1;//程式結束
	}
	buf[retVal] = '\0';//最後為空
	printf("received:%s\n", buf);//印出內容
	while (true) {//設定傳送內容 ******重點片段(c)******
		char carry[BUF_SIZE];//建立快取，判斷是否結束
		ZeroMemory(buf, BUF_SIZE);
		ZeroMemory(carry, BUF_SIZE);
		scanf("%s", &buf);//讀取輸入值
		strcpy(carry, buf);//設定快取
		printf("Sending:%s\n", buf);//顯示傳送內容
		retVal = send(sHost, buf, strlen(buf), 0); //傳送訊息
		if (retVal == SOCKET_ERROR) {//傳送是否成功
			printf("send failed!\n");//顯示錯誤訊息
			closesocket(sHost);//中斷與server的連線
			WSACleanup();//關閉WSADATA
			return -1;//程式結束
		}
		ZeroMemory(buf, BUF_SIZE);
		retVal = recv(sHost, buf, BUF_SIZE, 0);//接收訊息
		if (retVal == SOCKET_ERROR) {//接收是否成功
			printf("receiv failed!\n");//顯示錯誤訊息
			closesocket(sHost);//中斷與server的連線
			WSACleanup();//關閉WSADATA
			return -1;//程式結束
		}
		buf[retVal] = '\0';//最後為空
		printf("received:%s\n", buf);//印出內容
		if (carry[0] == 'E' && carry[1] == 'N' && carry[2] == 'D')//如果輸入"END"結束連線
			break;
	}
	getchar();
	closesocket(sHost);//中斷與server的連線
	return 0;
}