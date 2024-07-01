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
unsigned char* compress(unsigned char* out, int fileSize)
{
    unsigned char* temp;

    temp = BWT(out, &fileSize);
    free(out);
    out = temp;

    temp = MTF(out, fileSize);
    free(out);
    out = temp;

    out = huffman(out, &fileSize);

//    temp = MTF(out, fileSize);
//    free(out);
//    out = temp;
//
//    out = huffman(out, &fileSize);

    return out;
}
#endif //HUFFMAN_COMPRESS_H
