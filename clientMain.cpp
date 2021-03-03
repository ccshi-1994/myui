// SocketLearning.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsData;

    //开始环境
    if (WSAStartup(sockVersion, &wsData) != 0)
    {
        return 0;
    }

    //创建套接字
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        printf("client socket is invalid socket\n");
        return 0;
    }

    //服务器参数设置
    sockaddr_in severAddr;
    severAddr.sin_family = AF_INET;
    severAddr.sin_port = htons(7070);
    severAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    //连接服务器
    int ret = connect(clientSocket, (sockaddr*)&severAddr, sizeof(severAddr));
    if (ret == SOCKET_ERROR)
    {
        printf("client connect error!\n");
        closesocket(clientSocket);
        return 0;
    }

    char sendData[] = "hello, this is first client demo\n";
    send(clientSocket, sendData, strlen(sendData), 0);

    char recvData[4096];
    int recvSize = recv(clientSocket, recvData, 4096, 0);
    if (recvSize > 0)
    {
        recvData[recvSize] = '\0';
        printf("client recv data: %s", recvData);
    }

    //关闭套接字
    closesocket(clientSocket);
    WSACleanup();

    getchar();
    return 0;
}
