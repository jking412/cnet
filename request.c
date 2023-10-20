//
// Created by skynesser on 2023/10/5.
//
#include "cnet.h"
#include "main.h"

// º¯Êý²»ÆÆ»µÔ­×Ö·û´®
Request *parse_request(const char *req_str){
    Request *request = (Request *)malloc(sizeof(Request));
    request->req_str = strdup(req_str);

    char *req_str2 = strdup(req_str);

    char *body = strstr(req_str2,"\r\n\r\n") + 4;

    char *method = strtok(req_str2," ");
    char *path = strtok(NULL," ");
    char *version = strtok(NULL,"\r\n");



    request->method = strdup(method);
    request->path = strdup(path);
    request->version = strdup(version);
    request->body = strdup(body);

    free(req_str2);

    return request;
}

void free_req(Request *request){
    free(request->method);
    free(request->path);
    free(request->version);
    free(request->body);
    free(request);
}