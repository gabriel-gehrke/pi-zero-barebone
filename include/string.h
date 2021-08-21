#pragma once
#include "common.h"

// copies the contents of src int dest
void strcpy(char* dest, char* src);

// copies src to end of dest
void strcat(char* dest, char* src);

// calculates the length of the given string
u32 strlen(const char* str);