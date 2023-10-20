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

// serveHTTP ���ᴴ��һ��web server��Ĭ�ϼ���8080�˿�
int serveHTTP(char *port) {

    // ���ó�ʼ������������һ��server socket
    // ����Ϊ�˿ںţ�Ĭ��Ϊ3000
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

        // ���ܿͻ��˵�����
        ClientSocket = accept(listenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return ERR;
        }

        // ��������
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

    // ���岢��ʼ������
    WSADATA wsaData;

    SOCKET listenSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iResult;

    // Initialize Winsock, MAKEWORD(2,2)����2.2��
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return ERR;
    }

    ZeroMemory(&hints, sizeof(hints));
    // AF_INETָ��IPv4��ַ
    hints.ai_family = AF_INET;
    // SOCK_STREAM��IPPROTO_TCPָ��TCP����
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // ������������ַ�Ͷ˿ڵ�result��
    iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return ERR;
    }

    // ����һ��socket
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return ERR;
    }

    // ��socket����������ַ
    iResult = bind(listenSocket, result->ai_addr, (int) result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    // �ͷ�result��������Ҫ
    freeaddrinfo(result);

    // ��ʼ����socket
    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    return listenSocket;
}


