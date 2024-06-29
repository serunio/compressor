//
// Created by x7kub on 20.06.2024.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "tree.h"
#include "BWT.h"
#include "MTF.h"

void compress(char* plik)
{
    FILE* in = fopen(plik, "rb");

    int fileSize = 0;
    while (getc(in) != EOF)
        fileSize++;
    rewind(in);

    unsigned char* out = malloc((1+fileSize) * sizeof(char));
    unsigned  char* temp;

    int i = 0;
    int c;
    while ( (c = getc(in)) != EOF)
        out[i++] = (char)c;
    rewind(in);
    out[fileSize] = '\0';

    temp = BWT(out, &fileSize);
    free(out);
    out = temp;

    temp = MTF(out, fileSize);
    free(out);
    out = temp;

    Node_p* tree = malloc(256 * sizeof(Node_p));
    Node_p* array = malloc(256 * sizeof(Node_p));
    for(i = 0; i<256; i++)
    {
        tree[i] = newNode();
        tree[i]->frequency = 0;//rand()%20;
        tree[i]->symbol = (char)i;
        array[i] = tree[i];
    }
    int size = 256;

    getFrequencies(out, fileSize, array);
    clearArray(tree, &size);
    sortArray(tree, size, compareFrequency);
    buildTree(tree, &size);
    calculateDepth(array, 256);
    generateCodes(array, 256);

    temp = writeCompressed(out, &fileSize, array);
    free(out);
    out = temp;

    FILE* output = fopen("compressed.bin", "wb");
    for(i = 0; i < fileSize; i++)
        fprintf(output, "%c", out[i]);

    free(out);
}
#endif //HUFFMAN_COMPRESS_H
