#include "cnet.h"
#include "main.h"


static SOCKET init_winSock(char *port);

void handle_request(SOCKET client_socket) {
    Buffer* request_buf = read_from_socket(client_socket);
    Request *request = parse_request((const char *)request_buf->data);
    free_buffer(request_buf);

    request->client_socket = client_socket;

    Handler handler = search_route(request);
    handler(request);

    free_req(request);
    closesocket(client_socket);
}

// serveHTTP 将会创建一个web server，默认监听8080端口
int serveHTTP(char *port) {

    // 调用初始化函数，返回一个server socket
    // 参数为端口号，默认为3000
    SOCKET listenSocket = init_winSock(port);

    if (listenSocket == ERR) {
        printf("server failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    printf("web server run on port %s\n\n",port);

    do {
        SOCKET ClientSocket = INVALID_SOCKET;

        // 接受客户端的连接
        ClientSocket = accept(listenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return ERR;
        }

        // 处理请求
        handle_request(ClientSocket);

    } while (1);

    closesocket(listenSocket);
    WSACleanup();
    return OK;
}



static SOCKET init_winSock(char *port) {

    if (port == NULL) {
        port = DEFAULT_PORT;
    }

    // 定义并初始化变量
    WSADATA wsaData;

    SOCKET listenSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iResult;

    // Initialize Winsock, MAKEWORD(2,2)调用2.2版
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return ERR;
    }

    ZeroMemory(&hints, sizeof(hints));
    // AF_INET指定IPv4地址
    hints.ai_family = AF_INET;
    // SOCK_STREAM和IPPROTO_TCP指定TCP连接
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // 解析服务器地址和端口到result中
    iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return ERR;
    }

    // 创建一个socket
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return ERR;
    }

    // 绑定socket到服务器地址
    iResult = bind(listenSocket, result->ai_addr, (int) result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    // 释放result，不再需要
    freeaddrinfo(result);

    // 开始监听socket
    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    return listenSocket;
}


