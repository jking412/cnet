# cnet使用指南

## 1.背景

一个简单的库，使用C语言启动一个HTTP服务器。

## 2. 简介

cnet包含了一些基本功能，包括：
- [x] 注册路由
- [x] 支持静态资源请求
- [x] 支持表单解析

## 3. 快速开始

1. 首先引入cnet.h头文件，然后写一个Handler函数，接口如下：
```c
void (*Handler)(Request *req);
```
一个hello world的例子：
```c
void hello_world(Request *request){
    printf("%s\n",request->req_str);
    resp_string(request->client_socket,StatusOK,StatusTextOK,"Hello World!");
}
```

2. 然后注册路由：
```c
int register_route(char *method,char *path,Handler handler);
```
```c
register_route(GET,"/hello",hello_world);
```

3. 启动服务器：
使用`serveHTTP`函数启动服务器，参数为端口号。
```c
int serveHTTP(char *port);
```
完整的例子：
```c
#include "cnet.h"

void hello_world(Request *request){
    printf("%s\n",request->req_str);
    resp_string(request->client_socket,StatusOK,StatusTextOK,"Hello World!");
}

int main(){
    register_route(GET,"/hello",hello_world);
    serveHTTP("8080");
    return 0;
}
```
4. 编译运行：
```bash
make start
```
5. 访问测试
在浏览器中访问`http://localhost:8080/hello`，即可看到`Hello World!`。

## 4. 函数说明
