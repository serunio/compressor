//
// Created by x7kub on 20.06.2024.
//

#ifndef HUFFMAN_DECOMPRESS_H
#define HUFFMAN_DECOMPRESS_H

unsigned char* decompress(unsigned char* out, int fileSize)
{
    unsigned char* temp;

//    temp = decodeHuffman(out, &fileSize);
//    free(out);
//    out = temp;
//
//    temp = decodeMTF(out, fileSize);
//    free(out);
//    out = temp;

    temp = decodeHuffman(out, &fileSize);
    free(out);
    out = temp;

    temp = decodeMTF(out, fileSize);
    free(out);
    out = temp;

    temp = decodeBWT(out, &fileSize);
    free(out);
    out = temp;

    return out;
}
#endif //HUFFMAN_DECOMPRESS_H
