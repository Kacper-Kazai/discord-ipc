#pragma once
#include <stdint.h>
#include <stdlib.h>

struct base_pipe {
    static base_pipe* create();
    static void destroy(base_pipe*&);
    bool is_open{ false };
    bool open();
    bool close();
    bool write(const void* data, size_t length);
    bool read(void* data, size_t length);
};