cmake_minimum_required(VERSION 3.27)
project(huffman C)

set(CMAKE_C_STANDARD 11)

add_executable(huffman main.c
        tree.h
        tree.c
        huffman.c
        huffman.h
        byte.c
        byte.h
        compress.h
        decompress.h
        BWT.c
        BWT.h
        MTF.c
        MTF.h
)
