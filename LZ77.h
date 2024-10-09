//
// Created by jakub on 7/1/24.
//

#ifndef HUFFMAN_LZ77_H
#define HUFFMAN_LZ77_H

#include "byte.h"

typedef struct {
    byte buffor;
    unsigned char* string;
    int size;
} stream;

unsigned char* LZ77(const unsigned char* input, int* fileSize);

void addByteToStream(stream* s, unsigned char byte);
void addBitToStream(stream* s, unsigned char bit);

#endif //HUFFMAN_LZ77_H
