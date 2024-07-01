//
// Created by x7kub on 18.06.2024.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <stdbool.h>

typedef struct Node {
    unsigned char symbol;
    int frequency;
    int depth;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    char* bitCode;

} *Node_p, Node;

Node_p newNode();

void buildTree(Node_p* array, int* size);

void addToArray(Node_p* array, int* size, Node_p node);

void removeFromArray(Node_p* array, int* size, Node_p pattern);

void sortArray(Node_p* array, int size, int(*)(const Node_p*, const Node_p*));

int compareFrequency(const Node_p* a, const Node_p* b);
int compareDepth(const Node_p* a, const Node_p* b);
int compareSymbol(const Node_p* a, const Node_p* b);

void calculateDepth(Node_p* array, int size);
void generateCodes(Node_p* array, int size);

void clearArray(Node_p*, int* size);

void freeTree(Node_p);

void freeArray(Node_p* a);

#endif //HUFFMAN_TREE_H
