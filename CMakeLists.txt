cmake_minimum_required(VERSION 3.27)
project(huffman C)

set(CMAKE_C_STANDARD 11)

add_executable(huffman main.c
        tree.h
        tree.c
        files.c
        files.h
        byte.c
        byte.h
        compress.h
        decompress.h
)
