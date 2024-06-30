//
// Created by x7kub on 20.06.2024.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
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

    int i = 0, c;
    while ( (c = getc(in)) != EOF)
        out[i++] = (unsigned char)c;
    rewind(in);
    out[fileSize] = '\0';

    temp = BWT(out, &fileSize);
    free(out);
    out = temp;

    temp = MTF(out, fileSize);
    free(out);
    out = temp;

    out = huffman(out, &fileSize);

    plik = strcat(plik, ".cmp");
    FILE* output = fopen(plik, "wb");
    for(i = 0; i < fileSize; i++)
        fprintf(output, "%c", out[i]);

    free(out);
}
#endif //HUFFMAN_COMPRESS_H
