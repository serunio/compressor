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

int compareSymbols(const Node_p* a, const Node_p* b)
{
    return (*a)->symbol - (*b)->symbol;
}

void addToArray(Node_p* array, int* size, Node_p node)
{
    for(int i = 0; i <= *size; i++)
    {
        if (array[i]->frequency <= node->frequency)
        {
            for(int j = *size-i-1; j >= 0;j--)
            {
                array[j+i+1] = array[j+i];
            }
            array[i] = node;
            break;
        }
    }
    (*size)++;
}

void removeFromArray(Node_p* array, int* size, Node_p pattern)
{
    int i;
    for(i = 0; i < *size; i++)
    {
        if(array[i]->symbol == pattern->symbol)
            break;
    }
    for(i; i < *size; i++)
    {
        if(i != *size-1)
            array[i] = array[i+1];
    }
    (*size)--;

}

void printArray(Node_p* array, int size)
{
    printf("[ ");
    for(int i = 0; i < size; i++)
        printf("%d ", array[i]->frequency);
    printf("]\n[ ");
    for(int i = 0; i < size; i++)
        printf("%c ", array[i]->symbol);
    printf("]\n\n");

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
        //printArray(array, *size);
    }
}

void printCodes(Node_p* array, int size)
{
    Node_p temp;
    char code[257];
    code[256] = '\0';
    for(int i = 0; i < size; i++)
    {
        temp = array[i];
        //printf("%c ", array[i]->symbol);
        int j = 0;
        while(temp->parent != NULL)
        {
            code[255-j] = (char)(temp->bit + '0');
            temp = temp->parent;
            j++;
        }
        j--;
        //printf("%s\n", &code[255-j]);
        array[i]->bitCode = strdup(&code[255-j]);
    }
}

void clearArrays(Node_p* t, Node_p* a, int* size)
{

    for(int i = 0; i < *size; i++)
    {
        if(t[i]->frequency==0)
        {
            removeFromArray(t, size, t[i]);
            i--;
        }
    }
}