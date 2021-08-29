#pragma once
#include "common.h"
#include <stdbool.h>

// copies the contents of src int dest
void strcpy(char* dest, const char* src);

// copies src to end of dest
void strcat(char* dest, const char* src);

// calculates the length of the given string
u32 strlen(const char* str);

i32 strcmp(const char* str1, const char* str2);

static inline bool streql(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}