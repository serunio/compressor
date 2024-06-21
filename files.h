//
// Created by x7kub on 19.06.2024.
//

#ifndef HUFFMAN_FILES_H
#define HUFFMAN_FILES_H

#include <stdio.h>
#include "tree.h"

void getFrequencies(FILE* in, Node_p* array);

void writeCompressed(FILE* in, Node_p* array);

void getDepths(FILE* in, Node_p* array);

void writeDecompressed(FILE* in, Node_p* array);

#endif //HUFFMAN_FILES_H
