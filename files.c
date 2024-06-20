//
// Created by x7kub on 19.06.2024.
//

#include "files.h"
#include "byte.h"

void read(FILE* in, Node_p* array)
{
    int c;
    while((c = getc(in)) != EOF)
    {
        array[c]->frequency++;
    }
}

void write(FILE* in, Node_p* array)
{
    rewind(in);
    FILE* out = fopen("compressed.bin", "wb");
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