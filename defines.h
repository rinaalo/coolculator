#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef uint32_t u32;

typedef struct string {
    char *str;
    size_t size;
} string;
