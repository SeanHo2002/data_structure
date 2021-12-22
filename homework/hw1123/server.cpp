#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#define BUF_SIZE 1024
int main(int argc, char* argv[]) {
	int sockfd;//等待連線用socket_id
	int new_fd;//接受連線後新socket_id
	struct sockaddr_in my_addr;//local_server_ip_port
	struct sockaddr_in client_addr;//client_ip_port
	char buf[BUF_SIZE];
	int retVal;
	int sin_size;
	WSADATA wsd;
	retVal = WSAStartup(MAKEWORD(2, 2), &wsd);//啟動WSADATA
	if (retVal!=0) {//啟動是否成功
		printf("winsock startup failed!\n");//顯示錯誤訊息
		return -1;//程式結束
	}
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//建立socket代碼
	if (sockfd==-1) {//建立是否成功
		printf("socket() failed!\n");//顯示錯誤訊息
		WSACleanup();//關閉WSADATA
		return -1;//程式結束
	}
	my_addr.sin_family = AF_INET;//ipv4
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);//所有網卡
	my_addr.sin_port = htons((short)6666);//port ******重點片段(a)******
	sin_size = sizeof(my_addr);//my_addr的size
	retVal = bind(sockfd, (struct sockaddr*)&my_addr, sin_size);//綁定my_addr至sockfd
	if (retVal == -1) {//綁定是否成功
		printf("bind failed!\n");//顯示錯誤訊息
		closesocket(sockfd);//結束連線
		WSACleanup();//關閉WSADATA
		return -1;//程式結束
	}
	retVal = listen(sockfd, 10);//啟動監聽(最多等待10個連線)
	if (retVal == -1) {//啟動監聽是否成功
		printf("listening failed!\n");//顯示錯誤訊息
		closesocket(sockfd);//結束連線
		WSACleanup();//關閉WSADATA
		return -1;//程式結束
	}
	printf("server is running\n");//伺服器可運行
	new_fd = accept(sockfd, (struct sockaddr*)&client_addr, &sin_size);//確定連線
	if (new_fd == -1) {//連線不通過
		printf("accepting failed!\n");//顯示錯誤訊息
		//continue;//繼續接收下一個連線
	}
	memset(buf, 0, BUF_SIZE);
	retVal = recv(new_fd, buf, BUF_SIZE, 0);//接收訊息
	if (retVal <= 0) {//接收是否成功
		printf("recv error!close connection\n");//顯示錯誤訊息
		closesocket(new_fd);//結束連線
		return -1;//程式結束
	}
	buf[retVal] = '\0';//最後為空
	printf("r:%s", buf);//印出內容
	printf("\n", buf);//印出內容
	strcpy(buf, "Hello! This is a word count service.");//設定傳送內容 ******重點片段(b)******
	retVal = send(new_fd, buf, strlen(buf), 0); //傳送從客戶端收到的訊息
	if (retVal == SOCKET_ERROR) {//傳送是否成功
		printf("send failed!\n");//顯示錯誤訊息
		closesocket(new_fd);//結束連線
		WSACleanup();//關閉WSADATA
		return -1;//程式結束
	}
	while (true) {//持續接收訊息
		memset(buf, 0, BUF_SIZE);
		retVal = recv(new_fd, buf, BUF_SIZE, 0);//接收訊息
		if (retVal <= 0) {//接收是否成功
			printf("recv error!close connection\n");//顯示錯誤訊息
			closesocket(new_fd);//結束連線
			return -1;//程式結束
		}
		buf[retVal] = '\0';//最後為空
		printf("r:%s", buf);//印出內容
		char carry[BUF_SIZE];//建立快取，判斷是否結束
		ZeroMemory(carry, BUF_SIZE);
		strcpy(carry, buf);//設定快取
		printf("\n", buf);//印出內容
		int time = strlen(buf);//設定傳送內容為字串長度 ******重點片段(c)******
		_itoa(time,buf,10);////設定傳送內容為字串長度   ******重點片段(c)******
		retVal = send(new_fd, buf, strlen(buf), 0); //傳送訊息
		if (retVal == SOCKET_ERROR) {//傳送是否成功
			printf("send failed!\n");//顯示錯誤訊息
			closesocket(new_fd);//結束連線
			WSACleanup();//關閉WSADATA
			return -1;//程式結束
		}
		if (carry[0] == 'E' && carry[1] == 'N' && carry[2] == 'D') // 如果輸入"END"程式結束
			return -1;//程式結束
	}
	return 0;
}