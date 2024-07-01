//
// Created by x7kub on 18.06.2024.
//
#include "tree.h"
#include <stdlib.h>
#include <string.h>

Node_p newNode()
{
    Node_p n = malloc(sizeof(Node));
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    n->depth = 0;
    n->bitCode = strdup("");
    return n;
}

void sortArray(Node_p* array, int size, int(*compare)(const Node_p*, const Node_p*) )
{
    qsort(array, size, sizeof(Node_p), (int (*)(const void *, const void *)) compare);
}

int compareFrequency(const Node_p* a, const Node_p* b)
{
    return (*b)->frequency - (*a)->frequency;
}

int compareDepth(const Node_p* a, const Node_p* b)
{
    int result;
    if((result = (*b)->depth - (*a)->depth) == 0)
        result = (*a)->symbol - (*b)->symbol;
    return result;
}

int compareSymbol(const Node_p* a, const Node_p* b)
{
    return (*a)->symbol - (*b)->symbol;
}

void addToArray(Node_p* array, int* size, Node_p node)
{
    for(int i = 0; i <= *size; i++)
        if (array[i]->frequency <= node->frequency)
        {
            for(int j = *size-i-1; j >= 0;j--)
                array[j+i+1] = array[j+i];
            array[i] = node;
            break;
        }
    (*size)++;
}

void removeFromArray(Node_p* array, int* size, Node_p pattern)
{
    int i;
    for(i = 0; i < *size; i++)
        if(array[i]->symbol == pattern->symbol)
            break;
    for(; i < *size; i++)
        if(i != *size-1)
            array[i] = array[i+1];
    (*size)--;
}

void buildTree(Node_p* array, int* size)
{
    Node_p n, a, b;
    while(*size > 1)
    {
        n = newNode();
        b = array[(*size)-1];
        a = array[(*size)-2];
        n->frequency = a->frequency + b->frequency;
        n->symbol = a->symbol;

        a->parent = n;
        b->parent = n;

        n->left = a;
        n->right = b;

        removeFromArray(array, size, a);
        removeFromArray(array, size, b);
        addToArray(array, size, n);
    }
}

void calculateDepth(Node_p* array, int size)
{
    Node_p temp;
    Node_p node;
    for(int i = 0; i < size; i++)
    {
        node = temp = array[i];
        while(temp->parent != NULL)
        {
            node->depth++;
            temp = temp->parent;
        }
    }
}

void freeTree(Node_p node)
{
    if(node->left->left != NULL)
        freeTree(node->left);
    if(node->right->right != NULL)
        freeTree(node->right);
    free(node->bitCode);
    free(node);
}


void generateCodes(Node_p* array, int size)
{
    sortArray(array, size, compareDepth);

    int i = 0;
    int length = array[i]->depth;
    char* code = malloc(length+1);
    for(int k = 0; k < length; k++)
        code[k] = '0';
    code[length] = '\0';
    free(array[i]->bitCode);
    array[i]->bitCode = strdup(code);
    for(i++; array[i]->depth > 0; i++)
    {
        if(array[i]->depth < length)
        {
            while(length != array[i]->depth)
                code[--length] = '\0';
        }

        for(int j = length-1; j >= 0; j--)
        {
            if(code[j] == '0')
            {
                code[j] = '1';
                break;
            }
            else if(code[j] == '1')
                code[j] = '0';
        }
        free(array[i]->bitCode);
        array[i]->bitCode = strdup(code);
    }

    free(code);
    sortArray(array, size, compareSymbol);
}

void clearArray(Node_p* t, int* size)
{
    for(int i = 0; i < *size; i++)
        if(t[i]->frequency==0)
        {
            removeFromArray(t, size, t[i--]);
        }

}

void freeArray(Node_p* a)
{
    for(int i = 0; i<256; i++)
    {
        free(a[i]->bitCode);
        free(a[i]);
    }
    free(a);
}
