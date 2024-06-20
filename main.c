#include "compress.h"
#include "decompress.h"
#include <string.h>

int main(int argc, char** argv) {
    if(argc < 3)
        return 1;
    char* tryb = argv[1];
    char* plik = argv[2];
    if(!strcmp(tryb, "compress"))
        compress(plik);
    else if(!strcmp(tryb, "decompress"))
        decompress(plik);
    else return 1;
    return 0;
}
