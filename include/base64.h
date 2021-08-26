#pragma once
#include "common.h"

// encodes "src_len" bytes at "src" to base64 and stores them in "dest". The returned pointer points to the first character after the stored result.
char* base64_encode(char* dest, const char* src, u32 src_len);

// decodes "src_len" bytes at "src" from base64 and stores the result into "dest".
char* base64_decode(char* dest, const char* src, u32 src_len);