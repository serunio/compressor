//
// Created by x7kub on 19.06.2024.
//

#ifndef HUFFMAN_BYTE_H
#define HUFFMAN_BYTE_H

typedef struct byte {
    char c;
    short size;
} byte;

byte newByte();

int addToByte(byte*, char);

int isFull(byte*);

#endif //HUFFMAN_BYTE_H
