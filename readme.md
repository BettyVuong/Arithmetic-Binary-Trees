# CIS2520-F24-A3

### Student Information 
Name : Betty Vuong

Student Number : 1271673

### Assignment Overview
What is the assignment about?  
The assignment focuses on using binary trees and heaps for two components of the assignment.

The consists of two parts, part 1 and part 2. Part 1 is an arithmetic binary tree. Part 2 is a max-heap generator.

## Part 1
For binary trees, the program takes an input of an expresssion that is parenthesized and creates an arithmetic binary tree. Then, the program can output the traversal of the binary tree depending on the traversal technique. The program can also compute calculations using the binary tree. If there are variables, the program accomodates for user input for the values as well.


**Compile the Program**
First, type in "make". Then, type in "./a3q1 'expression'" to run the program. For example to pass (((1.56+4.26)*(x1-2.23))/x2), use this command line input "./a3q1 '(((x1+5.12)*(x2-7.68))/x3)'". The user have either feedback on their input or user will be prompted with a menu.

## Part 2
For the heap part of the assignment, the program reads a 200 2-digit integer text file that stores integers in an array of 20 rows and 10 columns. The program then creates a max-heap with the given array and prints it.

**Compile The Program**
First, type in "make". Then, type in "./a3q2" to run the program. The user will be displayed with an array visual of max-heap.

### Resources 
I used examples from the course lecture slides such as the trees and heaps to refer and manipulate my data structures. I also used my RPN code from assignment 2 question 2 as a base code for my calculations in this assignment question 1. Since the format of post-order is how rpn computes its values. For heaps, the max-heap populating function was based off of the course lecture slides 22-23 of heaps.

### Implementation
The assignment is complete and has a robust input handling for question 1, this ensures that the input aligns with the construction of the binary tree and the calculations are accurate without breaking the code. User can input many cases such as missing brackets at certain points, missing operators, incorrect variables, and more and the program will either handle the case or terminate the program early.