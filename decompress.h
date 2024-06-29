//
// Created by x7kub on 20.06.2024.
//

#ifndef HUFFMAN_DECOMPRESS_H
#define HUFFMAN_DECOMPRESS_H

void decompress(char* plik)
{
    FILE* in = fopen(plik, "rb");
    FILE* output = fopen("decompressed.txt", "wb");
    Node_p* array = malloc(256 * sizeof(Node_p));
    unsigned char* out;
    unsigned char* temp;
    int fileSize = 0, c, i;
    for(i = 0; i < 256; i++)
    {
        array[i] = newNode();
        array[i]->symbol = (char)i;
    }
    getDepths(in, array);
    generateCodes(array, 256);
    rewind(in);
    while(getc(in) != EOF)
        fileSize++;
    rewind(in);
    out = malloc(fileSize*sizeof(unsigned char));
    i = 0;
    while((c = getc(in)) != EOF)
        out[i++] = c;

    temp = decodeHuffman(out, array, &fileSize);
    free(out);
    out = temp;

    temp = decodeMTF(out, fileSize);
    free(out);
    out = temp;

    temp = decodeBWT(out, &fileSize);
    free(out);
    out = temp;

    for(i = 0; i < fileSize; i++)
        fprintf(output, "%c", out[i]);
}

#endif //HUFFMAN_DECOMPRESS_H
