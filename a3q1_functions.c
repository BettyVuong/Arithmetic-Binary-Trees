/*
Name: Betty Vuong
Student ID: 1271673
Assignment 3, Question 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"

Variable variables[10];
// int varCount = 0;

// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node *createNode(char *data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    strcpy(temp->data, data); // copying string to node
    temp->left = NULL;        // child set to null
    temp->right = NULL;       // child set to null

    return temp;
}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node *parseExpression(char *expr)
{
    // input validation
    int brackPair = 0, operands = 0, operator= 0;
    // check for correct acount of operators and operands
    for (int i = 0; i < strlen(expr); i++)
    {
        // correct number of brackets in pairs
        if (expr[i] == '(' || expr[i] == ')')
        {
            brackPair++;
        }
        // checks if the value is float
        if (isdigit(expr[i]))
        {
            if (expr[i + 1] == '.' && !isdigit(expr[i + 4]) && isdigit(expr[i + 3]))
            { // checks if its below 10 or the decimal values are only
                // the next four characters are float

                // update i
                i += 3; // this will skip the next three indexes
                operands++;
            }
            else
            {
                if (isdigit(expr[i + 4]))
                {
                    printf("\nThe value entered has more than two decimal places, format should be y.yy.");
                }
                else
                {
                    printf("\nThe value entered is greater than 9.99, not a float value, or doesn't follow the format y.yy.");
                }
                // end program
                exit(1);
            }
        }
        // check for operands
        if (expr[i] == '+' || expr[i] == '*' || expr[i] == '/' || expr[i] == '-')
        {
            operator++;
        }

        // check for variables
        if (expr[i] == 'x' || expr[i] == 'X')
        { // if variable
            // check for two cases, 1-9 and 10
            if (isdigit(expr[i + 2]))
            { // checks for two digits
                char num[3];
                num[0] = expr[i + 1]; // first digit
                num[1] = expr[i + 2]; // second digit
                num[2] = '\0';
                int check = atoi(num); // convert to int
                // checking if ts equal to 10
                if (check == 10)
                {
                    char variable[3];
                    variable[0] = expr[i];
                    strcat(variable, num); // variable created

                    // update i
                    i += 2;
                    operands++;
                }
                else
                {
                    printf("\nVariable is not valid, where Xn subscript n, n ≥ 10.");
                    exit(1);
                }
            }
            else
            { // checks for single digit 1-9
                if (isdigit(expr[i + 1]))
                {
                    int num = expr[i + 1] - '0';
                    if (num >= 1 && num <= 9)
                    { // within the range
                        // update i
                        i += 1;

                        operands++;
                    }
                    else
                    {
                        printf("\nVariable is not valid, where Xn subscript n, n ≥ 10.");
                        exit(1);
                    }
                }
                else
                {
                    printf("\nVariable does not follow the format Xn.");
                    exit(1);
                }
            }
        }

        // check if expression is anything but '()+-*/xX' or 0-9
        // if(!isdigit(expr[i]) || expr[i] != '(' || expr[i] != ')' || expr[i] != '+' || expr[i] != '-' || expr[i] != '*' || expr[i] != '/' || expr[i] != 'x' || expr[i] != 'X'){
        //  printf("\nExpression contains values that are not within the guidelines of '()+-*/xX' or 0-9");
        //  exit(1);
        //}
    }

    // checking for proper bracket pairs
    if (brackPair % 2 != 0)
    {
        printf("\nExpression contains uneven pairs of brackets.");
        exit(1);
    }

    //no brackets case
    if(brackPair == 0){
        printf("\nNo brackets were provided in the expression, binary tree cannot be computed.");
        exit(1);
    }

    // checking for proper amounts of operators and operands
    if (operator!= operands - 1)
    {
        printf("\nExpression contains uneven arithmetic, there are more operands or operators than an expression can have or an invalid operator\n");
        exit(1);
    }

    // create stacks to start parsing
    // for brackets
    Bracket *bracket = NULL;
    // for operators
    NodeStack *operators = NULL;
    // for values
    NodeStack *nodes = NULL;

    // parsing
    // checking for different cases to push and pop from stacks
    for (int i = 0; i < strlen(expr); i++)
    {
        // for open bracket
        if (expr[i] == '(')
        {
            char *character = (char[2]){expr[i], '\0'};
            // push to bracket stack
            pushStr(&bracket, character);
        }
        else if (isdigit(expr[i]))
        { // check for float
            // check if the next four characters equal to the float format y.yy
            if (expr[i + 1] == '.' && !isdigit(expr[i + 4]))
            { // checks if its below 10 or the decimal values are only
                // the next four characters are float
                // copy the other indexes
                char num[5];
                num[0] = expr[i];
                num[1] = expr[i + 1];
                num[2] = expr[i + 2];
                num[3] = expr[i + 3];
                num[4] = '\0';

                // update i
                i += 3; // this will skip the next three indexes

                // create leaf node
                Node *temp = createNode(num);
                // push node
                pushNode(&nodes, temp);
            }
            else
            {
                if (isdigit(expr[i + 4]))
                {
                    printf("\nThe value entered has more than two decimal places, format should be y.yy.");
                }
                else
                {
                    printf("\nThe value entered is greater than 9.99, or not a float value.");
                }
                // end program
                exit(1);
            }
        }
        else if (expr[i] == 'x' || expr[i] == 'X')
        { // if variable
            // check for two cases, 1-9 and 10
            if (isdigit(expr[i + 2]))
            { // checks for two digits
                char num[3];
                num[0] = expr[i + 1]; // first digit
                num[1] = expr[i + 2]; // second digit
                num[2] = '\0';
                int check = atoi(num); // convert to int
                // checking if ts equal to 10
                if (check == 10)
                {
                    char variable[3];
                    variable[0] = expr[i];
                    strcat(variable, num); // variable created

                    // update i
                    i += 2;
                    // create node
                    Node *temp = createNode(variable);
                    // push node
                    pushNode(&nodes, temp);
                }
                else
                {
                    printf("\nVariable is not valid, where Xn subscript n, n ≥ 10.");
                    exit(1);
                }
            }
            else
            { // checks for single digit 1-9
                if (isdigit(expr[i + 1]))
                {
                    int num = expr[i + 1] - '0';
                    if (num >= 1 && num <= 9)
                    { // within the range
                        char variable[3];
                        variable[0] = expr[i];
                        variable[1] = expr[i + 1];
                        variable[2] = '\0';
                        // update i
                        i += 1;

                        // create node
                        Node *temp = createNode(variable);
                        // push node into stack
                        pushNode(&nodes, temp);
                    }
                    else
                    {
                        printf("\nVariable is not valid, where Xn subscript n, n ≥ 10.");
                        exit(1);
                    }
                }
                else
                {
                    printf("\nVariable does not follow the format Xn.");
                    exit(1);
                }
            }
        }
        else if (expr[i] == '+' || expr[i] == '*' || expr[i] == '/' || expr[i] == '-')
        { // operands
            // create node
            char op[2];
            op[0] = expr[i];
            op[1] = '\0';
            Node *temp = createNode(op);
            // push onto operand stack
            pushNode(&operators, temp);
        }
        else if (expr[i] == ')')
        {                                       // layer of depth in the expression is found, compute a tree
            popStr(&bracket);                   // pops a bracket
            Node *parent = popNode(&operators); // parent node
            Node *rightChild = popNode(&nodes); // right node
            Node *leftChild = popNode(&nodes);  // left node

            // build tree
            parent->right = rightChild;
            parent->left = leftChild;

            // push node onto stack of nodes
            pushNode(&nodes, parent);
        }
        else
        {
            printf("\nThe format of the expression does not follow the specific input, program is terminated.");
            exit(1);
        }
    }

    // pop the root node
    Node *root = popNode(&nodes);

    // swapping the children trees of the root if the left is smaller than right
    // calculate the depth of each subtree
    depth(root);
    int swap = varCount;

    // see if swap is needed
    // swap the trees
    if (swap == 1)
    {
        Node *swapNode = (Node *)malloc(sizeof(Node));
        swapNode = root->left;    // holds left tree
        root->left = root->right; // swap left to right
        root->right = swapNode;   // now place left to right
    }

    return root;
}

// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        printf("%s ", root->data);

        // recursive call left branch
        preorder(root->left);

        // recursive call right branch
        preorder(root->right);
    }
}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root)
{
    if (root == NULL) // base case
    {
        return;
    }
    else // traverse the tree, recursive case
    {
        printf("(");
        // recursive call the left branch
        inorder(root->left);

        printf("%s", root->data);

        // recursive call teh right branch
        inorder(root->right);

        printf(")");
    }
}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        // recursive call left
        postorder(root->left);
        // recursive call right
        postorder(root->right);
        printf("%s ", root->data);
    }
}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root)
{
    // pushing all nodes to stack
    NodeStack *stack = NULL;
    NodeToStack(root, &stack);

    Node *trav = root;

    // traverse to find variable
    // for left branch
    while (stack != NULL)
    {
        trav = popNode(&stack);
        if (trav->left == NULL && trav->right == NULL)
        {
            char data[5];
            strcpy(data, trav->data);

            // check for duplicates if leaf node is a variable
            int dupe = 0; // no dupe
            if (!isdigit(data[0]))
            {
                // check for duplicates
                if (varCount != 0)
                { // if array isnt empty
                    for (int i = 0; i < varCount; i++)
                    {
                        char comp[5];
                        strcpy(comp, variables[i].varName);
                        // if there's dupe
                        if (strcmp(comp, data) == 0)
                        {
                            dupe = 1; // flag as true
                            break;
                        }
                    }
                }
            }

            // create a new node for array if theres no variable dupe and is a variable
            if (dupe == 0 && !isdigit(data[0]))
            {
                int correct = 0;
                float value;
                do
                {
                    // prompt user for input
                    printf("\nEnter float value for %s:", data);
                    scanf("%f", &value);
                    if (value < 10.00 && value > -10.00)
                    {
                        correct = 1;
                        // printf("hi");
                    }
                    else
                    {
                        printf("\nValue must be less than 10.00.\n");
                        correct = 0;
                    }
                } while (correct == 0);

                // copy values into array
                strcpy(variables[varCount].varName, data);
                variables[varCount].value = value;
                // printf("\n%f", value);
                varCount++;
            }
        }
    }
}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root)
{
    // push nodes into stack
    NodeStack *stack = NULL;
    NodeStack *reverseStck = NULL;
    Numbers *calculator = NULL;
    reversePushStack(root, &stack);

    // printStack(stack);

    // reverse the stack
    while (stack != NULL)
    {
        Node *temp = popNode(&stack);
        Node *update = (Node *)malloc(sizeof(Node));
        int flag = 0;
        // change the values for variables
        char data[5];
        strcpy(update->data, temp->data);
        update->left = NULL;
        update->right = NULL;
        strcpy(data, update->data);
        strcpy(data, temp->data);
        if (data[0] == 'x' || data[0] == 'X')
        {
            // variable found
            for (int i = 0; i < varCount; i++)
            {
                // update to a float value
                if (strcmp(data, variables[i].varName) == 0)
                {
                    char value[6];
                    snprintf(value, sizeof(value), "%.2f", variables[i].value);
                    strcpy(update->data, value);
                    flag = 1;
                }
            }
        }
        if (flag == 0)
        {
            pushNode(&reverseStck, temp);
        }
        else
        {
            pushNode(&reverseStck, update);
        }
    }
    // printStack(reverseStck);
    while (reverseStck != NULL)
    {
        Node *trav = popNode(&reverseStck);

        char data[6];
        strcpy(data, trav->data);
        // two cases, value, and operator
        if (isdigit(data[0]) || (data[0] == '-' && isdigit(data[1])))
        {
            float value = atof(data);
            pushNum(&calculator, value);
        }
        else
        {
            float val1, val2;
            if (calculator != NULL || calculator->next != NULL)
            {
                val1 = popNum(&calculator);
            }
            else
            {
                return 0;
            }
            if (calculator != NULL)
            {
                val2 = popNum(&calculator);
            }
            else
            {
                return 0;
            }
            if (strcmp(data, "+") == 0)
            {
                float ans = val2 + val1;
                pushNum(&calculator, ans);
            }
            else if (strcmp(data, "-") == 0)
            {
                float ans = val2 - val1;
                pushNum(&calculator, ans);
            }
            else if (strcmp(data, "*") == 0)
            {
                float ans = val1 * val2;
                pushNum(&calculator, ans);
            }
            else if (strcmp(data, "/") == 0)
            {
                // check if div 0
                if (val1 == 0)
                {
                    printf("\nDivision by 0, not a valid.\n");
                    return 0;
                }
                else
                {
                    float ans = val2 / val1;
                    pushNum(&calculator, ans);
                }
            }
            else
            {
                printf("\nUnknown operator\n");
                return 0;
            }
        }
    }

    // clear variable array values after you're done
    for (int i = 0; i < varCount; i++)
    {
        variables[i].value = 0;
    }
    // get total
    float total = popNum(&calculator);
    return total;
}

// push nodes from tree into stack
void NodeToStack(Node *root, NodeStack **stack)
{
    if (root == NULL)
    { // base case
        return;
    }
    else
    { // recursive case
        pushNode(stack, root);

        if (root->left != NULL)
        {
            NodeToStack(root->left, stack);
        }

        if (root->right != NULL)
        {
            NodeToStack(root->right, stack);
        }
    }
}

// pushes values from tree in post order, reverse.
void reversePushStack(Node *root, NodeStack **stack)
{
    if (root == NULL)
    { // base case
        return;
    }
    else
    { // recursive case
        // traverse left first

        if (root->left != NULL)
        {
            reversePushStack(root->left, stack);
        }

        if (root->right != NULL)
        {
            reversePushStack(root->right, stack);
        }

        pushNode(stack, root);
    }
}

// push strings into the stack
void pushStr(Bracket **stack, char bracket[2])
{
    Bracket *temp = (Bracket *)malloc(sizeof(Bracket));
    strcpy(temp->op, bracket);
    temp->next = *stack;
    *stack = temp;
}

// pop strings from the stack
char *popStr(Bracket **stack)
{
    char *str = malloc(2);
    Bracket *temp = *stack;
    *stack = (*stack)->next;
    strcpy(str, temp->op);
    free(temp);
    return str;
}

// push node into stack
void pushNode(NodeStack **stack, Node *value)
{
    NodeStack *temp = (NodeStack *)malloc(sizeof(NodeStack));
    temp->curNode = value;
    temp->next = *stack;
    *stack = temp;
}

// pop node from stack
Node *popNode(NodeStack **stack)
{
    Node *current = (Node *)malloc(sizeof(Node));
    NodeStack *temp = *stack;
    *stack = (*stack)->next;
    current = temp->curNode;
    free(temp);
    return current;
}

// pushes a new value into stack
void pushNum(Numbers **stack, float num)
{
    Numbers *temp = (Numbers *)malloc(sizeof(Numbers));
    temp->num = num;
    temp->next = *stack;
    *stack = temp;
}

// pops value from top of the stack
float popNum(Numbers **stack)
{
    if (*stack == NULL)
    {
        printf("\nstack empty");
        return 0;
    }
    Numbers *temp = *stack;
    *stack = (*stack)->next;
    float num = temp->num;
    free(temp);
    return num;
}

int depth(Node *root)
{
    int rightDepth = 0, leftDepth = 0;
    // base case
    if (root == NULL)
    {
        return 0;
        // recursive case
    }
    else
    {
        leftDepth = depth(root->left);
        rightDepth = depth(root->right);
        if (rightDepth > leftDepth)
        {
            varCount = 1;
            rightDepth++;
            return rightDepth;
        }
        else
        {
            leftDepth++;
            return leftDepth;
        }
    }
}

void freeTree(Node *root){
    //base case
    if(root == NULL){
        return;
        //recursive case
    } else{
        //traverse each case
        freeTree(root -> left);
        freeTree(root -> right);

        free(root);
    }
}
