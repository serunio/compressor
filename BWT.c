//
// Created by x7kub on 22.06.2024.
//

#include "BWT.h"
#include <stdlib.h>
#include <string.h>

int length;
unsigned  char* lastSymbol;
unsigned char* BWT(unsigned char* input, int* oldFileSize)
{
    int fileSize = *oldFileSize;
    length = fileSize;
    unsigned char* output = malloc(4+fileSize);
    unsigned char** array = malloc(fileSize*sizeof(unsigned char*));
    unsigned char* contents = malloc(2*fileSize*sizeof(unsigned char));
    for(int i = 0; i < fileSize; i++ )
    {
        contents[i] = contents[i+fileSize] = input[i];
        array[i] = &(contents[i]);
    }
    output[fileSize+3] = '\0';
    lastSymbol = array[fileSize-1];
    unsigned char* firstSymbol = array[0];
    unsigned int lastSymbolNumber = -1;
    qsort(array, fileSize, sizeof(unsigned char*), (int (*)(const void *, const void *))sortPointers);

    if(&array[0][fileSize-1] == lastSymbol)
        lastSymbolNumber = 0;
    for(int j = fileSize-1; j >= 0; j--)
    {
        if(array[j] == firstSymbol)
        {
            output[j+4] = *lastSymbol;
            lastSymbolNumber = j;
        }
        else
            output[j+4] = array[j][-1];
    }

    for(int j = 1; j <= 4; j++)
        output[j-1] = (char)((lastSymbolNumber>>(32-(8*j))) & 0xff);

    free(array);
    (*oldFileSize) += 4;
    return output;
}

unsigned char* decodeBWT(unsigned char* input, int* oldFileSize)
{
    int fileSize = *oldFileSize;
    int lastSymbolIndeks = 0;
    for(int i = 0; i < 4; i++)
        lastSymbolIndeks += (int)input[i] << (32-(i+1)*8);
    unsigned char* lastColumn = malloc((fileSize-4)*sizeof(unsigned char));
    int** firstColumn = malloc((fileSize-4)*sizeof(int*));
        for(int i = 0; i < fileSize - 4; i++)
        {
            firstColumn[i] = malloc(2*sizeof(int));
            lastColumn[i] = input[i+4];
            firstColumn[i][0] = (int)input[i+4];
            firstColumn[i][1] = i;
        }

    qsort(firstColumn, fileSize-4, sizeof(int*),  (int(*)(const void*, const void*))sortFirstColumn);
    unsigned char* output = malloc((fileSize-3)*sizeof(unsigned char));
    int indeks = lastSymbolIndeks;
    output[fileSize-5] = lastColumn[indeks];
    for(int i = 0; i <= fileSize - 6; i++)
    {
        output[i] = (unsigned char)firstColumn[indeks][0];
        indeks = firstColumn[indeks][1];
    }
    output[fileSize-4] = '\0';
    free(lastColumn);
    for(int i = 0; i < fileSize - 4; i++)
        free(firstColumn[i]);
    free(firstColumn);
    (*oldFileSize) -= 4;
    return output;
}

int sortPointers(const unsigned char** a, const unsigned char** b)
{
    return strcmp( (const char *)*a, (const char *)*b);
}

int sortFirstColumn(const int** a, const int** b)
{
    int result = a[0][0] - b[0][0];
    if(result == 0)
        result = a[0][1] - b[0][1];
    return result;
}