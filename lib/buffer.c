//
// Created by skynesser on 2023/10/19.
//
#include "buffer.h"

Buffer *new_buffer() {
    return new_buffer_with_cap(DEFAULT_BUFFER_SIZE);
}

Buffer *new_buffer_with_cap(int cap) {
    Buffer *buffer = (Buffer *) malloc(sizeof(Buffer));
    buffer->data = (uint8_t *) calloc(1,sizeof(uint8_t) * cap);
    buffer->len = 0;
    buffer->cap = cap;

    return buffer;
}

Buffer *buffer_grow(Buffer *buffer, int cap) {
    if (buffer->cap >= cap) {
        return buffer;
    }

    uint8_t *data = (uint8_t *) malloc(sizeof(uint8_t) * cap);
    memcpy(data, buffer->data, buffer->len);
    free(buffer->data);
    buffer->data = data;
    buffer->cap = cap;

    return buffer;
}

Buffer *buffer_append_byte(Buffer *buffer, uint8_t byte) {
    buffer_grow(buffer, buffer->len + 1);
    buffer->data[buffer->len] = byte;
    buffer->len++;

    return buffer;
}

Buffer* buffer_append_char(Buffer *buffer, char c) {
    return buffer_append_byte(buffer, (uint8_t) c);
}

Buffer* buffer_append_str(Buffer *buffer, char *str) {
    return buffer_append(buffer, (uint8_t *) str, strlen(str));
}

Buffer* buffer_append(Buffer *buffer, uint8_t *data, int len) {
    buffer_grow(buffer, buffer->len + len);
    memcpy(buffer->data + buffer->len, data, len);
    buffer->len += len;
    return buffer;
}

void free_buffer(Buffer *buffer) {
    free(buffer->data);
    free(buffer);
}