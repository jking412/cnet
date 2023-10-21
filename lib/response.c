//
// Created by skynesser on 2023/10/5.
//
#include "cnet.h"
#include "main.h"

#define HTTP_RESP HTTP_DEFAULT_HEADER "%s"
#define HTTP_DEFAULT_HEADER HTTP_VERSION " %d %s\r\n" \
                            "Content-Type: text/html\r\n" \
                            "Content-Length: %I64d\r\n" \
                            "\r\n"
#define HTTP_VERSION "HTTP/1.1"


void resp_string(SOCKET client_socket,int status_code,char *status,char *content){

    long long content_length = strlen(content);
    char bytes[1024 + content_length];
    sprintf(bytes,HTTP_RESP,status_code,status,content_length,content);

    send(client_socket,bytes,strlen(bytes),0);
}