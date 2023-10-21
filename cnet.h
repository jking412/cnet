#ifndef CNET_LIBRARY_H
#define CNET_LIBRARY_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <assert.h>
#include <string.h>
#include "lib/buffer.h"

typedef struct Form{
    int len;
    char **key;
    char **value;
}Form;

typedef struct {
    const char *req_str;

    char *method;
    char *path;
    char *version;
    char *body;

    SOCKET client_socket;
} Request;

typedef void (*Handler)(Request *req);

typedef struct {
    char *method;
    char *path;
    Handler handler;
} Route;

extern Route routes[];


#define DEFAULT_PORT "8080"
#define OK 0
#define ERR (-1)

#define MAX_ROUTE 100

#define StatusOK 200
#define StatusMovedPermanently 301
#define StatusBadRequest 400
#define StatusNotFound 404
#define StatusInternalServerError 500

#define StatusTextOK "OK"
#define StatusTextMovedPermanently "Moved Permanently"
#define StatusTextBadRequest "Bad Request"
#define StatusTextNotFound "Not Found"
#define StatusTextInternalServerError "Internal Server Error"

#define GET "GET"
#define POST "POST"

int serveHTTP(char *port);
void resp_string(SOCKET client_socket,int status_code,char *status,char *content);

int register_route(char *method,char *path,Handler handler);

Form *parse_form(const char *req_body);
void free_form(Form *form);



#endif //CNET_LIBRARY_H
