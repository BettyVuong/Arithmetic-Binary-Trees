/*
Name: Betty Vuong
Student ID: 1271673
Assignment 3, Question 2
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the smallest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
 * Code is referenced and based from CIS*2520 lecture slides on Heap
*/
void downHeap(int key[20], int pos, int array[20][10]){
  int childIndex = 2*pos+1; //left child index
  int value = key[pos]; //value of the key

  int maxValue, maxIndex, arraySize = 20;

  while(childIndex < arraySize){ //seeing if it reaches the last node
    maxValue = value; //current node value from key
    maxIndex = -1; //null

    //checking for left and right children
    for(int i = 0; i <= 1; i++){ 
      //checking if a child exists
      if(childIndex + i < arraySize){
        if(key[childIndex+i] > maxValue){ //if child max is greater then the current max value, swap
        //updating updating
          maxValue = key[childIndex+i];
          maxIndex = childIndex +i;
        }
      }
    }

    if(maxValue == value){ //is max value is at the right position
      return;
    } else{
      swap(pos, maxIndex, key, array); // swap with the larger child
      pos = maxIndex;
      childIndex = 2*pos+1;
    }
  }
}

// The isParent function returns true if the passed position has a child or false if there's no child
bool isParent(int keyPos){
  int childIndex = 2*keyPos+1;
  if (childIndex < 20){ //ensuring its not out of bounds
    return true; //has min of one child, thus parent
  }
  return false; //not a parent

}

// The swap function swaps 2 rows in the 2D array and the key array. It receives the position of the 2 rows to be swapped, the key array, and the 2D array in its arguements.
void swap(int key1Pos, int key2Pos, int key[20], int array[20][10]){
  //swapping the positions
  int temp = key[key1Pos];
  key[key1Pos] = key[key2Pos];
  key[key2Pos] = temp;
  
  //performing swap on rows
  int tempRow [10];

  //copying the rows and looping the arrays
  for(int i = 0; i < 10; i++){
    tempRow[i] = array[key1Pos][i];
    array[key1Pos][i] = array[key2Pos][i];
    array[key2Pos][i] = tempRow[i];
  }

}
