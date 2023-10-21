//
// Created by skynesser on 2023/10/10.
//
#include "cnet.h"

Form *parse_form(const char *req_body){
    Form *form = (Form*)malloc(sizeof(Form));
    form->len = 0;
    form->key = NULL;
    form->value = NULL;

    int str_len = 0;
    for(int i = 0 ; req_body[i] ; i++){
        if(req_body[i] == '&')form->len++;
        str_len++;
    }

    if(str_len == 0)return form;

    form->len++;

    form->key = (char**)malloc((sizeof (char*)) * form->len);
    form->value = (char**)malloc((sizeof (char*)) * form->len);

    int is_key = 1;
    int start_idx = 0;
    int idx = 0;


    for(int i = 0 ; i <= str_len ; i++){
        if(is_key && req_body[i] == '='){
            int len = i - start_idx;

            char *key = malloc(sizeof(char) * (len + 1));
            strncpy(key,req_body + start_idx,len);
            key[len] = '\0';

            start_idx = i + 1;
            is_key = 0;

            form->key[idx] = key;
        }else if((!is_key && req_body[i] == '&' )|| (!is_key && req_body[i] == '\0')) {
            int len = i - start_idx;

            char *val = malloc(sizeof(char) * (len + 1));
            strncpy(val, req_body + start_idx, len);
            val[len] = '\0';

            start_idx = i + 1;
            is_key = 1;

            form->value[idx] = val;

            idx++;
        }
    }

    assert(idx == form->len);

    return form;
}

void free_form(Form *form){
    for(int i = 0 ; i < form->len ; i++){
        free(form->key[i]);
        free(form->value[i]);
    }
    free(form->key);
    free(form->value);
    free(form);
}