//
// Created by x7kub on 22.06.2024.
//

#ifndef HUFFMAN_BWT_H
#define HUFFMAN_BWT_H

#include <stdio.h>

unsigned char* BWT(unsigned char* contents, int* fileSize);

unsigned char* decodeBWT(unsigned char* input, int* fileSize);

int sortPointers(const unsigned char**, const unsigned char**);

int sortFirstColumn(const int** a, const int** b);

#endif //HUFFMAN_BWT_H
