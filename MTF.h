//
// Created by x7kub on 24.06.2024.
//

#ifndef HUFFMAN_MTF_H
#define HUFFMAN_MTF_H

unsigned char* MTF(const unsigned char* in, int length);

unsigned char* decodeMTF(unsigned char* in, int length);

void moveCharToFront(unsigned char* symbols, int index);

#endif //HUFFMAN_MTF_H
