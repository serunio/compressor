//
// Created by x7kub on 20.06.2024.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "tree.h"

void compress(char* plik)
{
    Node_p* tree = malloc(256 * sizeof(Node_p));
    Node_p* array = malloc(256 * sizeof(Node_p));
    for(int i = 0; i<256; i++)
    {
        tree[i] = newNode();
        tree[i]->frequency = 0;//rand()%20;
        tree[i]->symbol = (char)i;
        array[i] = tree[i];
    }
    int size = 256;
    FILE* in = fopen(plik, "rb");
    read(in, array);
    clearArrays(tree, array, &size);
    sortArray(tree, size, compareFrequency);
    buildTree(tree, &size);
    printCodes(array, 256);
    write(in, array);
    sortArray(array, 256, compareFrequency);
    for( int i = 0; i < 256; i++)
    {
        printf("%3d %s\n", array[i]->symbol, array[i]->bitCode);
    }
}
#endif //HUFFMAN_COMPRESS_H
