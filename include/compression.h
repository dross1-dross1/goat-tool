
// include/compression.h

#ifndef COMPRESSION_H
#define COMPRESSION_H

char* compress_string(const char* str);
char* decompress_string(const char* str);
int compress_goat(const char* filename);
int decompress_goat(const char* filename);

#endif // COMPRESSION_H
