//
// Created by x7kub on 19.06.2024.
//

#include "files.h"
#include "byte.h"
#include <string.h>
#include <stdlib.h>

void getFrequencies(const unsigned char* in, int size, Node_p* array)
{
    for(int i = 0; i < size; i++)
        array[in[i]]->frequency++;
}

unsigned char* writeCompressed(const unsigned char* in, int* oldSize, Node_p* array)
{
    int size = (*oldSize);
    //FILE* out = fopen("compressed.bin", "wb");
    unsigned char* outt = malloc((257+size)*sizeof(unsigned char));

    outt[size+256] = '\0';
    int i, result, outputtedByteCount = 0;
    for(i = 0; i < 256; i++)
        //fprintf(out, "%c", array[i]->depth);
        outt[outputtedByteCount++] = (unsigned char)array[i]->depth;
    char bin;
    byte b;
    b = newByte();
    for(int j = 0 ; j < size; j++)
    {
        i = 0;
        while(true)
        {
            bin = array[in[j]]->bitCode[i++];
            if(bin == '\0')
                break;
            result = addToByte(&b, bin);

            if(result == 2)
            {
                //fprintf(out, "%c", b.c);
                outt[outputtedByteCount++] = b.c;

                b = newByte();
            }
        }
    }

    if(addToByte(&b, '1') == 2)
    {
        //fprintf(out, "%c", b.c);
        outt[outputtedByteCount++] = b.c;
        b = newByte();
    }
    while(!isFull(&b))
    {
        addToByte(&b, '0');
    }
    //fprintf(out, "%c", b.c);
    outt[outputtedByteCount++] = b.c;
    *oldSize = outputtedByteCount;
    return outt;
}

void getDepths(FILE* in, Node_p* array)
{
    for(int i = 0; i < 256; i++)
        array[i]->depth = getc(in);
}

unsigned char* decodeHuffman(unsigned char* in, Node_p* array, int* inputSymbolCount)
{
    unsigned char* out;
    int newSymbolCount = 0;
    unsigned char byte;
    unsigned char bit;
    char* code = strdup("");

    int bitCount = 8*(*inputSymbolCount - 256);

    byte = in[*inputSymbolCount-1];
    for(int i = 0; i < 8; i++) {
        bit = byte & (char)1;
        byte = byte >> 1;
        bitCount--;
        if(bit == 1)
            goto a;
    }
    bitCount--;
a:
    out = malloc(bitCount*sizeof(char));

    for(int j = 256; true; j++)
    {
        byte = in[j];
        for(int i = 0; i < 8; i++)
        {
            bit = byte >> 7;
            byte = byte << 1;

            if(bit == 1)
                strcat(code, "1");
            else if(bit == 0)
                strcat(code, "0");
            for(int j = 0; j < 256; j++)
            {
                if(!strcmp(code, array[j]->bitCode))
                {
                    out[newSymbolCount] = array[j]->symbol;
                    code = strdup("");
                    newSymbolCount++;
                    break;
                }
            }
            if(!bitCount--)
            {
                newSymbolCount--;
                *inputSymbolCount = newSymbolCount;
                return out;
            }
        }
    }
//    *inputSymbolCount = newSymbolCount;
//    return out;
}