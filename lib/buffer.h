//
// Created by skynesser on 2023/10/19.
//

#ifndef CNET_BUFFER_H
#define CNET_BUFFER_H

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint8_t *data;
    int len;
    int cap;
} Buffer;

#define DEFAULT_BUFFER_SIZE 1024

Buffer *new_buffer();
Buffer *new_buffer_with_cap(int cap);
Buffer *buffer_grow(Buffer *buffer, int cap);

Buffer *buffer_append_byte(Buffer *buffer, uint8_t byte);
Buffer *buffer_append_char(Buffer *buffer, char c);
Buffer *buffer_append_str(Buffer *buffer, char *str);

Buffer *buffer_append(Buffer *buffer, uint8_t *data, int len);
void free_buffer(Buffer *buffer);


#endif //CNET_BUFFER_H
