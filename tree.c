//
// Created by x7kub on 18.06.2024.
//
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node_p newNode()
{
    Node_p n = malloc(sizeof(Node));
    n->parent = NULL;
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
    if((result = (*a)->depth - (*b)->depth) == 0)
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
    for(i; i < *size; i++)
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

        a->bit = 0;
        b->bit = 1;

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

void generateCodes(Node_p* array, int size)
{
    sortArray(array, size, compareDepth);

    int i = 0;
    while(array[i]->depth == 0)
        i++;
    int length = array[i]->depth;
    char* code = malloc(length+1);
    for(int k = 0; k < length; k++)
        code[k] = '0';
    code[length] = '\0';
    array[i]->bitCode = strdup(code);
    for(i++; i < 256; i++)
    {
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

        if(array[i]->depth > length)
        {
            strcat(code, "0");
            length++;
        }
        array[i]->bitCode = strdup(code);
    }

    //free(code);
    sortArray(array, size, compareSymbol);
}

void clearArrays(Node_p* t, Node_p* a, int* size)
{
    for(int i = 0; i < *size; i++)
        if(t[i]->frequency==0)
            removeFromArray(t, size, t[i--]);
}