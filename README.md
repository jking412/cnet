# cnetʹ��ָ��

## 1.����

һ���򵥵Ŀ⣬ʹ��C��������һ��HTTP��������

## 2. ���

cnet������һЩ�������ܣ�������
- [x] ע��·��
- [x] ֧�־�̬��Դ����
- [x] ֧�ֱ�����

## 3. ���ٿ�ʼ

1. ��������cnet.hͷ�ļ���Ȼ��дһ��Handler�������ӿ����£�
```c
void (*Handler)(Request *req);
```
һ��hello world�����ӣ�
```c
void hello_world(Request *request){
    printf("%s\n",request->req_str);
    resp_string(request->client_socket,StatusOK,StatusTextOK,"Hello World!");
}
```

2. Ȼ��ע��·�ɣ�
```c
int register_route(char *method,char *path,Handler handler);
```
```c
register_route(GET,"/hello",hello_world);
```

3. ������������
ʹ��`serveHTTP`��������������������Ϊ�˿ںš�
```c
int serveHTTP(char *port);
```
���������ӣ�
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
4. �������У�
```bash
make start
```
5. ���ʲ���
��������з���`http://localhost:8080/hello`�����ɿ���`Hello World!`��

## 4. ����˵��
