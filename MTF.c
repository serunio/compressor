//
// Created by x7kub on 24.06.2024.
//

#include "MTF.h"
#include <stdlib.h>

unsigned char* MTF(const unsigned char* in, int length)
{
    unsigned char* output = malloc((length+1*sizeof(char)));
    unsigned char symbols[256];
    for(int i = 0; i < 256; i++)
    {
        symbols[i] = (unsigned char)i;
    }
    unsigned char current;
    for(int i = 0; i < length; i++)
    {
        current = in[i];
        for(int j = 0; j < 256; j++)
        {
            if(symbols[j] == current)
            {
                output[i] = (unsigned char)j;
                moveCharToFront(symbols, j);
                break;
            }
        }
    }
    return output;
}

unsigned char* decodeMTF(unsigned char* in, int length)
{
    unsigned char* output = malloc((length+1*sizeof(unsigned char)));
    unsigned char symbols[256];
    for(int i = 0; i < 256; i++)
    {
        symbols[i] = (unsigned char)i;
    }
    for(int i = 0; i < length; i++)
    {
        output[i] = symbols[in[i]];
        //printf("%d ", output[i]);
        moveCharToFront(symbols, in[i]);
    }
    return output;
}

void moveCharToFront(unsigned char* symbols, int index)
{
    unsigned char s = symbols[index];
    for(int i = index; i > 0; i--)
    {
        symbols[i] = symbols[i-1];
    }
    symbols[0] = s;
}
