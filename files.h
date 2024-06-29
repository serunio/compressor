//
// Created by x7kub on 19.06.2024.
//

#ifndef HUFFMAN_FILES_H
#define HUFFMAN_FILES_H

#include <stdio.h>
#include "tree.h"

void getFrequencies(const unsigned char* in, int size, Node_p* array);

unsigned char* writeCompressed(const unsigned char* in, int* size, Node_p* array);

void getDepths(FILE* in, Node_p* array);

unsigned char* decodeHuffman(unsigned char* in, Node_p* array, int* symbolCount);

#endif //HUFFMAN_FILES_H
