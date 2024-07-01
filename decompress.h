//
// Created by x7kub on 20.06.2024.
//

#ifndef HUFFMAN_DECOMPRESS_H
#define HUFFMAN_DECOMPRESS_H

void decompress(char* plik)
{
    FILE* in = fopen(plik, "rb");
    int fileSize = 0;
    while(getc(in) != EOF)
        fileSize++;
    rewind(in);
    unsigned char* out = malloc(fileSize*sizeof(unsigned char));
    for(int i = 0; i < fileSize; i++)
        out[i] = getc(in);
    fclose(in);

    unsigned char* temp;

    temp = decodeHuffman(out, &fileSize);
    free(out);
    out = temp;

    temp = decodeMTF(out, fileSize);
    free(out);
    out = temp;

//    temp = decodeHuffman(out, &fileSize);
//    free(out);
//    out = temp;
//
//    temp = decodeMTF(out, fileSize);
//    free(out);
//    out = temp;

    temp = decodeBWT(out, &fileSize);
    free(out);
    out = temp;

    plik = strcat(plik, "_decmp.txt");
    FILE* output = fopen(plik, "wb");
    for(int i = 0; i < fileSize; i++)
        fprintf(output, "%c", out[i]);
    fclose(output);
    free(out);
}

#endif //HUFFMAN_DECOMPRESS_H
