#include "compress.h"
#include "decompress.h"
#include <string.h>

int main(int argc, char** argv) {
    if(argc < 3)
        return 1;
    char* tryb = argv[1];
    char* plik = argv[2];

    FILE* in = fopen(plik, "r");
    if(in==NULL)
    {
        printf("plik %s nie istnieje\n", plik);
        return 1;
    }
    int fileSize = 0;
    while (getc(in) != EOF)
        fileSize++;
    rewind(in);
    unsigned char* out = malloc(fileSize*sizeof(unsigned char));
    for(int i = 0; i < fileSize; i++)
        out[i] = getc(in);
    fclose(in);

    if(!strcmp(tryb, "compress"))
    {
        out = compress(out, &fileSize);
        //out = decompress(out, &fileSize);
        plik = strcat(plik, ".cmp");
    }
    else if(!strcmp(tryb, "decompress"))
    {
        out = decompress(out, &fileSize);
        plik = strcat(plik, "_decmp.txt");
    }
    else return 1;

    FILE* output = fopen(plik, "w");
    for(int i = 0; i < fileSize; i++)
        fprintf(output, "%c", out[i]);
    fclose(output);
    free(out);

    return 0;
}
