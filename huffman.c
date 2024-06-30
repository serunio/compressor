//
// Created by x7kub on 19.06.2024.
//

#include "huffman.h"
#include "byte.h"
#include <string.h>
#include <stdlib.h>

unsigned char* huffman(unsigned char* in, int* oldSize)
{
    int fileSize = *oldSize;
    unsigned char* temp;
    Node_p* tree = malloc(256 * sizeof(Node_p));
    Node_p* array = malloc(256 * sizeof(Node_p));
    for(int i = 0; i<256; i++)
    {
        tree[i] = newNode();
        tree[i]->frequency = 0;//rand()%20;
        tree[i]->symbol = (char)i;
        array[i] = tree[i];
    }
    int size = 256;

    getFrequencies(in, fileSize, array);
    clearArray(tree, &size);
    sortArray(tree, size, compareFrequency);
    buildTree(tree, &size);
    calculateDepth(array, 256);
    generateCodes(array, 256);

    temp = encode(in, &fileSize, array);
    free(in);
    in = temp;

    free(temp);
    free(array);
    *oldSize = fileSize;
    return in;
}

void getFrequencies(const unsigned char* in, int size, Node_p* array)
{
    for(int i = 0; i < size; i++)
        array[in[i]]->frequency++;
}

unsigned char* encode(const unsigned char* in, int* oldSize, Node_p* array)
{
    int size = (*oldSize);
    unsigned char* outt = malloc((257+size)*sizeof(unsigned char));

    outt[size+256] = '\0';
    int i, result, outputtedByteCount = 0;
    for(i = 0; i < 256; i++)
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
                outt[outputtedByteCount++] = b.c;

                b = newByte();
            }
        }
    }

    if(addToByte(&b, '1') == 2)
    {
        outt[outputtedByteCount++] = b.c;
        b = newByte();
    }
    while(!isFull(&b))
    {
        addToByte(&b, '0');
    }
    outt[outputtedByteCount++] = b.c;
    *oldSize = outputtedByteCount;
    return outt;
}

void getDepths(FILE* in, Node_p* array)
{
    for(int i = 0; i < 256; i++)
        array[i]->depth = getc(in);
}

unsigned char* decode(unsigned char* in, Node_p* array, int* symbolCount)
{
    unsigned char* out;
    int newSymbolCount = 0;
    unsigned char byte;
    unsigned char bit;
    char* code = strdup("");

    int bitCount = 8*(*symbolCount - 256);

    byte = in[*symbolCount - 1];
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

    for(int k = 256; true; k++)
    {
        byte = in[k];
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
                *symbolCount = newSymbolCount;
                return out;
            }
        }
    }
//    *inputSymbolCount = newSymbolCount;
//    return out;
}