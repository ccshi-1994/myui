// serverSocket.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")


int main()
{
    //初始化环境
    WSADATA wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);

    SOCKADDR_IN srcAddr, clientAddr;
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    srcAddr.sin_port = htons(7070);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    bind(serverSocket, (sockaddr*)&srcAddr, sizeof(srcAddr));
    listen(serverSocket, 100);
    while (true)
    {
        int size = sizeof clientAddr;
        SOCKET clientSock = accept(serverSocket, (sockaddr*)&clientAddr, &size);

        std::thread td([&clientSock]() {
            char buf[4096];
            int recvSize = recv(clientSock, buf, 4096, 0);
            if (recvSize > 0)
            {
                buf[recvSize-1] = '\0';
                printf("recv data: %s\n", buf);
                char sendbuf[] = "this is sever send\n";
                send(clientSock, sendbuf, strlen(sendbuf), 0);
            }

            });
        td.join();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

