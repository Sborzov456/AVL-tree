#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "SecondaryFunctions.h"

#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct info {
    char *info;
    struct info *next;
} info;

typedef struct node //item of tree
{
    struct node *parent;
    struct node *left;
    struct node *right;
    info *info; //list of information
    int key;
    int balance;
} node;

//Working with node functions
node *create(node *root);
node *search(node *root, int key); //search info by key
info *addItemToInfoList(info *inf, char *information);
node *add(node *root, int key, char *information); //add item to the node
node *findMin(node *root); //find item with minimal key in subtree
node *findMax(node *root); //find item with maximal key in subtree
int findFurthestItem(node *root, int key); //find the item, which key difference with data most
node *extract(node *root, int key); //delete item and rebalance after that
int height(node *root); //height of node
void print(node *root, int lvl); //print node in console



//Balance functions
node *searchUnbalancedNode(node *leaf);
int calculateNodeBalance(node *item); //calculate and set balance of item
node *rotateRight(node *p, node **root);
node *rotateLeft(node *rotationNode, node **root);
node *balance(node *unbalancedNode, node **root); //balance the node
void recountBalance(node *root); //recount balance of each item



#endif //AVL_TREE_H
