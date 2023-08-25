#pragma once

#include <stdint.h>

#ifndef COOL_ALLOC
#include <stdlib.h>
#define COOL_ALLOC malloc
#endif

typedef uint32_t u32;
typedef double f64;

typedef struct string {
    char *str;
    size_t size;
} string;

