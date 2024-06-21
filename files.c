//
// Created by x7kub on 19.06.2024.
//

#include "files.h"
#include "byte.h"
#include <string.h>
#include <stdlib.h>

void getFrequencies(FILE* in, Node_p* array)
{
    int c;
    while((c = getc(in)) != EOF)
    {
        array[c]->frequency++;
    }
}

void writeCompressed(FILE* in, Node_p* array)
{
    rewind(in);
    FILE* out = fopen("compressed.bin", "wb");
    for(int i = 0; i < 256; i++)
        fprintf(out, "%c", array[i]->depth);
    int c, i, result;
    char bin;
    byte b;
    b = newByte();
    while((c = getc(in)) != EOF)
    {
        i = 0;
        while(true)
        {
            bin = array[c]->bitCode[i++];
            if(bin == '\0')
                break;
            result = addToByte(&b, bin);

            if(result == 2)
            {
                fprintf(out, "%c", b.c);
                b = newByte();
            }
        }
    }

    if(addToByte(&b, '1') == 2)
    {
        fprintf(out, "%c", b.c);
        b = newByte();
    }
    while(!isFull(&b))
    {
        addToByte(&b, '0');
    }
    fprintf(out, "%c", b.c);
}

void getDepths(FILE* in, Node_p* array)
{
    for(int i = 0; i < 256; i++)
        array[i]->depth = getc(in);
}

void writeDecompressed(FILE* in, Node_p* array)
{
    FILE* out = fopen("decompressed.txt", "wb");
    int byteI;
    unsigned char byte;
    unsigned char bit;
    char* code = strdup("");

    int bitCount = 0;
    while(getc(in) != EOF)
        bitCount++;
    bitCount *= 8;
    fseek(in, -1, SEEK_CUR);
    byteI = getc(in);
    byte = (unsigned char)byteI;
    do {
        bit = byte & (char)1;
        byte = byte >> 1;
        bitCount--;
    } while(bit == 0);

    fseek(in, 256, SEEK_SET);
    while((byteI = getc(in)) != EOF)
    {
        byte = (unsigned char)byteI;
        for(int i = 0; i < 8; i++)
        {
            bit = byte & (char)128;
            byte = byte << 1;
            if(bit == 128)
                strcat(code, "1");
            else if(bit == 0)
                strcat(code, "0");
            for(int j = 0; j < 256; j++)
            {
                if(!strcmp(code, array[j]->bitCode))
                {
                    fprintf(out, "%c", array[j]->symbol);
                    code = strdup("");
                    break;
                }
            }
            if(!bitCount--)
                return;
        }
    }
}