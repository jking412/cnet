//
// Created by skynesser on 2023/10/5.
//
#include "cnet.h"

void hello_world(Request *request){
    printf("%s\n",request->req_str);
    resp_string(request->client_socket,StatusOK,StatusTextOK,"Hello World!");
}

void login(Request *request){
    Form * form = parse_form(request->body);
    char resp[4096];
    sprintf(resp,"%s = %s,%s = %s\n",form->key[0],form->value[0],form->key[1],form->value[1]);
    free_form(form);
    resp_string(request->client_socket,StatusOK,StatusTextOK,resp);
}

int main(){
    register_route(GET,"/hello",hello_world);
    register_route(POST,"/login",login);
    serveHTTP("8080");
    return 0;
}