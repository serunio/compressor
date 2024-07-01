//
// Created by x7kub on 19.06.2024.
//

#include "byte.h"
#include <stdlib.h>

byte newByte()
{
    byte* b = malloc(sizeof(byte));
    b->size = 0;
    b->c = 0;
    byte result = *b;
    free(b);
    return result;
}

int addToByte(byte* b, char c)
{
    if(isFull(b))
        return 0;
    b->size++;
    b->c *= 2;
    if(c=='1')
        b->c++;
    if(isFull(b))
        return 2;
    return 1;
}

int isFull(byte* b)
{
    return b->size == 8;
}