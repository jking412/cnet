//
// Created by skynesser on 2023/10/5.
//
#include "cnet.h"
#include "main.h"


Route routes[MAX_ROUTE];
int route_count = 0;

void handler_404(Request *request) {
    resp_string(request->client_socket, StatusNotFound, StatusTextNotFound,"404 Not Found");
}

void handler_static_file(Request *request) {
    char *path = req2file_path(request->path);
//    char *content = read_full_file(path);
    Buffer *buffer = read_full_file(path);
    resp_string(request->client_socket, StatusOK,StatusTextOK, (char*)buffer->data);
    free_buffer(buffer);
}


int register_route(char *method, char *path, Handler handler) {
    if (route_count >= MAX_ROUTE) {
        printf("too many routes!\n");
        return -1;
    }

    routes[route_count].method = method;
    routes[route_count].path = path;
    routes[route_count].handler = handler;

    route_count++;

    return 0;
}


Handler search_route(Request *request) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].method, request->method) == 0 && strcmp(routes[i].path, request->path) == 0) {
            return routes[i].handler;
        }
    }

    // 查看查询path下是否存在对应的静态文件
    char *path = req2file_path(request->path);
    if (!access(path, F_OK)) {
        return handler_static_file;
    }


    return handler_404;
}

// 将路径转为相对路径
char *req2file_path(char *path) {
    char *file_path = (char *) malloc(sizeof(char) * (strlen(path) + 2));
    strcpy(file_path, ".");
    strcat(file_path, path);
    return file_path;
}