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
#include "LZ77.h"
unsigned char* compress(unsigned char* out, int* fileSize)
{
    unsigned char* temp;

    temp = BWT(out, fileSize);
    free(out);
    out = temp;

    temp = MTF(out, *fileSize);
    free(out);
    out = temp;

    out = huffman(out, fileSize);

//    temp = decodeHuffman(out, fileSize);
//    free(out);
//    out = temp;
//
//    temp = decodeMTF(out, *fileSize);
//    free(out);
//    out = temp;
//
//    temp = decodeBWT(out, fileSize);
//    free(out);
//    out = temp;

    return out;
}
#endif //HUFFMAN_COMPRESS_H
