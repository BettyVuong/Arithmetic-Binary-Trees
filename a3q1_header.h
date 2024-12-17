/*
Name: Betty Vuong
Student ID: 1271673
Assignment 3, Question 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef BINARY_TREE
#define BINARY_TREE

// Node structure representing a binary tree node containing string data.
typedef struct Node {
    char data[10];
    struct Node *left, *right;
} Node;

// Structure that stores variable names and their associated values.
typedef struct {
    char varName[10];
    float value;
} Variable;

typedef struct Bracket{
    char op[2];
    struct Bracket *next;
} Bracket;

typedef struct NodeStack{
    struct Node * curNode;
    struct NodeStack *next;
} NodeStack;

typedef struct Numbers{
    float num;
    struct Numbers * next;
} Numbers;

extern Variable variables[10];
extern int varCount;

Node* createNode(char *data);
Node* parseExpression(char *expr);
void preorder(Node *root);
void inorder(Node *root);
void postorder(Node *root);
void promptVariables(Node *root);
float calculate(Node *root);
void pushStr(Bracket** stack, char op [2]);
char* popStr(Bracket** stack);
void pushNode(NodeStack ** stack, Node * temp);
Node* popNode(NodeStack** stack);
char * print(Node * current);
void NodeToStack(Node *root, NodeStack ** stack);
void reversePushStack(Node *root, NodeStack ** stack);
void pushNum(Numbers ** stack, float num);
float popNum(Numbers ** stack);
int depth(Node *root);
void freeTree(Node *root);



#endif
