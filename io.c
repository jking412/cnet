//
// Created by skynesser on 2023/10/5.
//
#include "cnet.h"
#include "main.h"


Buffer *read_from_socket(SOCKET client_socket) {

//    static char request_str[MAX_MESSAGE];
//    memset(request_str, 0, MAX_MESSAGE);
//
//    if (recv(client_socket, request_str, MAX_MESSAGE, 0) >= MAX_MESSAGE - 1) {
//        printf("request message too long!\n");
//    }
//
//    request_str[MAX_MESSAGE - 1] = '\0';
//
//    return request_str;

    Buffer *buffer = new_buffer();
    uint8_t byte[DEFAULT_BUFFER_SIZE];
    int len;
    while ((len = recv(client_socket, (char*)byte, DEFAULT_BUFFER_SIZE, 0)) > 0) {
        buffer_append(buffer, byte, len);
        if (len < DEFAULT_BUFFER_SIZE) {
            break;
        }
    }

    buffer_append_char(buffer, '\0');

    return buffer;
}

Buffer *read_full_file(char *file_path) {
//    FILE *fp = fopen(file_path, "r");
//    if (fp == NULL) {
//        printf("file not found!\n");
//        return NULL;
//    }
//
//    fseek(fp, 0, SEEK_END);
//    int length = ftell(fp);
//    fseek(fp, 0, SEEK_SET);
//
//    char *content = (char *) malloc(sizeof(char) * (length + 1));
//    memset(content, 0, length);
//    fread(content, 1, length, fp);
//    fclose(fp);

    Buffer *buffer = new_buffer();
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("file not found!\n");
        return NULL;
    }

    uint8_t byte[DEFAULT_BUFFER_SIZE];
    int len;
    while ((len = fread(byte, 1, DEFAULT_BUFFER_SIZE, fp)) > 0) {
        buffer_append(buffer, byte, len);
        if(len != DEFAULT_BUFFER_SIZE){
            break;
        }
    }
    fclose(fp);

    return buffer;
}

