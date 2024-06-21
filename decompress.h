//
// Created by x7kub on 20.06.2024.
//

#ifndef HUFFMAN_DECOMPRESS_H
#define HUFFMAN_DECOMPRESS_H

void decompress(char* plik)
{
    FILE* in = fopen(plik, "rb");
    Node_p* array = malloc(256 * sizeof(Node_p));
    for(int i = 0; i<256; i++)
    {
        array[i] = newNode();
        array[i]->symbol = (char)i;
    }
    getDepths(in, array);
    generateCodes(array, 256);
    writeDecompressed(in, array);
}

#endif //HUFFMAN_DECOMPRESS_H
