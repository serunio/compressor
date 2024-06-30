//
// Created by x7kub on 19.06.2024.
//

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

#include <stdio.h>
#include "tree.h"

void getFrequencies(const unsigned char* in, int size, Node_p* array);

unsigned char* encode(const unsigned char* in, int* oldSize, Node_p* array);

void getDepths(FILE* in, Node_p* array);

unsigned char* decode(unsigned char* in, Node_p* array, int* symbolCount);

unsigned char* huffman(unsigned char* in, int* oldSize);

#endif //HUFFMAN_HUFFMAN_H
