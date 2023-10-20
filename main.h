//
// Created by skynesser on 2023/10/5.
//

#ifndef CNET_MAIN_H
#define CNET_MAIN_H

#include "cnet.h"

#define MAX_MESSAGE 4096


Buffer *read_from_socket(SOCKET client_socket);
Buffer *read_full_file(char *file_path);

Handler search_route(Request *request);
Request *parse_request(const char *req_str);
char *req2file_path(char *path);

void free_req(Request *request);    // 释放request结构体内存
#endif //CNET_MAIN_H
