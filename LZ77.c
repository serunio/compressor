//
// Created by jakub on 7/1/24.
//

#include <malloc.h>
#include <string.h>
#include "LZ77.h"


unsigned char* LZ77(const unsigned char* input, int* fileSize)
{
    int lookAheadBufferIndex = 3;
    int searchBufferIndex = 0;
    int searchBufferOffset = 10;
    stream out;
    out.buffor = newByte();
    out.size = 0;
    out.string = malloc(*fileSize);

    char* lookAheadString = malloc(4);
    char* searchString = malloc(4);

    printf("%c\n%c\n%c\n", input[0], input[1], input[2]);
    for(int i = 0; i < 3; i++)
    {
        addBitToStream(&out, 0);
        addByteToStream(&out, input[i]);
    }

    int length, offset;
    int i;
    while(lookAheadBufferIndex < *fileSize) {
        for (i = 0; searchBufferIndex + i != lookAheadBufferIndex; i++) {
            if (input[searchBufferIndex + i] == input[lookAheadBufferIndex]) {

                for (length = 0; length < 3; length++) {
                    searchString[length] = (char) input[searchBufferIndex + i + length];
                    lookAheadString[length] = (char) input[lookAheadBufferIndex + length];
                }
                searchString[3] = lookAheadString[3] = '\0';
                if (strcmp(searchString, lookAheadString) != 0)
                    continue;
                while (length) {
                    if (input[searchBufferIndex + i + length] != input[lookAheadBufferIndex + length])
                        break;
                    length++;
                }
                offset = lookAheadBufferIndex - searchBufferIndex - i;
                printf("%d %d\n", offset, length);
                addBitToStream(&out, 1);
                addByteToStream(&out, offset);
                addByteToStream(&out, length);
                lookAheadBufferIndex += length;
                break;
            }
        }
        if (searchBufferIndex + i == lookAheadBufferIndex)
        {
            printf("%c\n", input[lookAheadBufferIndex]);
            addBitToStream(&out, 0);
            addByteToStream(&out, input[lookAheadBufferIndex]);

            lookAheadBufferIndex++;
        }
        if(lookAheadBufferIndex-searchBufferIndex > searchBufferOffset)
            searchBufferIndex = lookAheadBufferIndex - searchBufferOffset;
    }
    *fileSize = out.size;
    return out.string;
}

void addByteToStream(stream* s, unsigned char byte)
{
    unsigned char bit;
    for(int i = 7; i >= 0; i--)
    {
        bit = byte >> i & (unsigned char)1;
        addBitToStream(s, bit);
    }
}
void addBitToStream(stream* s, unsigned char bit)
{
    int result = addToByte(&s->buffor, (char)(bit + '0'));
    if(result==2) {
        s->string[s->size++] = s->buffor.c;
        s->buffor = newByte();
    }

}

