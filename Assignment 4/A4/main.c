#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mhDefs.h"
#include "stuDefs.h"
#include "extraDefs.h"


int main()
{
  HeapType *heap;
  void  *ptr1, *ptr2, *ptr3, *ptr4;

  heap = (HeapType *) malloc(sizeof(HeapType));
  mh_init(heap);

  ptr1 = mh_alloc(heap, 5*sizeof(int), "ints");
  ptr2 = mh_alloc(heap, 10*sizeof(double), "doubles");
  ptr3 = mh_alloc(heap, 8*sizeof(char), "chars");
  ptr4 = mh_alloc(heap, 12*sizeof(StudentType), "Students");

  printf("\nDUMP 1, byte count = %d\n", mh_count(heap));
  mh_dump(heap);

  mh_dealloc(heap, ptr1);
  mh_dealloc(heap, ptr2);
  mh_dealloc(heap, ptr3);

  printf("\nDUMP 2, byte count = %d\n", mh_count(heap));
  mh_dump(heap);

  mh_collect(heap);

  printf("\nDUMP 3, byte count = %d\n", mh_count(heap));
  mh_dump(heap);
  printf("\n\n");

  mh_cleanup(heap);
  free(heap);

  // ADDITIONAL TESTING 

  printf("-------------------");
  printf("\nADDITIONAL TESTING\n");
  printf("-------------------\n");

  HeapType *heap2;                                    // The second heap on which we will do the additional testing.
  heap2 = (HeapType *) malloc(sizeof(HeapType));

  mh_init(heap2);

  void  *ptr5, *ptr6, *ptr7, *ptr8, *ptr9;            // These will point to the five additional data types we will be testing

  //Allocate memory for 4 new structures
  ptr5 = mh_alloc(heap2, 14*sizeof(float), "floats");
  ptr6 = mh_alloc(heap2, 25*sizeof(CityType), "Cities");
  ptr7 = mh_alloc(heap2, 6*sizeof(ShoeType), "Shoes");
  ptr8 = mh_alloc(heap2, 3*sizeof(TableType), "Tables");

  printf("\nDUMP 1, byte count = %d\n", mh_count(heap2));
  mh_dump(heap2);

  //Deallocate two of the four newly added structures
  mh_dealloc(heap2, ptr7);
  mh_dealloc(heap2, ptr8);

  printf("\nDUMP 2, byte count = %d\n", mh_count(heap2));
  mh_dump(heap2);

  //Add the 5th structure
  ptr9 = mh_alloc(heap2, 9*sizeof(FoodType), "Foods");

  printf("\nDUMP 3, byte count = %d\n", mh_count(heap2));
  mh_dump(heap2);

  //Deallocate everything reamining
  mh_collect(heap2);

  printf("\nDUMP 4, byte count = %d\n", mh_count(heap2));
  mh_dump(heap2);
  printf("\n\n");

  mh_cleanup(heap2);
  free(heap2);

  return 0;
}

//this function initializes the heap variable declared in main, including the dynamic allocation
void  mh_init(HeapType *heap){
	heap->head = NULL;
}

//this function frees the memory allocated for all the blocks in the heap parameter
void  mh_cleanup(HeapType *heap){
  while (heap->head != NULL){
    //free (heap->head->data->addr);
    free (heap->head->data);
    heap->head = heap->head->next;
  }
}

/*
using malloc , this function dynamically allocates a new block of memory of size n bytes 
adds the new block of memory as the next element of the blocks array in the heap parameter
saves the address of the new memory in that blocks element , as well as its size and a user-defined label to indicate the use for this block, and it sets the block s element to reserved 
itreturns the pointer returned by malloc
*/

void *mh_alloc(HeapType *heap, int n, char *label){

  //Allocate new memory
  void *newData = (void *) malloc(n);

  //Allocate new block
  BlockType *newBlock = malloc(sizeof(BlockType));

  //Initialize every field in block
  newBlock->addr = newData;
  newBlock->size = n;
  newBlock->rsv = C_TRUE;
  strcpy(newBlock->tag,label);

  //Allocate and initialize new node
  BlockNode *newNode;
  newNode = (BlockNode *) malloc(sizeof(BlockNode));
  newNode->data = newBlock;

  BlockNode *currNode = heap->head;
  BlockNode *prevNode = currNode;

  //Add node to the end of the linked list
  if (currNode == NULL){
    heap->head= newNode;
    newNode->next = currNode;
  }
  else{
    while (currNode != NULL){
      prevNode = currNode;
      currNode = currNode->next;
    }
    prevNode->next = newNode;
    newNode->next = currNode;//NULL
  }

	return newData;
}

/*
finds the blocks element in the heap parameter that corresponds to the block of memory pointed to by addr 
deallocates the memory pointed to by addr using free
*/
void  mh_dealloc(HeapType *heap, void *addr){
  BlockNode *currNode = heap->head;
  BlockNode *prevNode = heap->head;

  // Accounting for the case in which we're removing the only node left and for removing first element (the head)
  if (currNode->data->addr == addr){
    heap->head = currNode->next;
    free(currNode->data->addr);
    free(currNode->data);
    free(currNode);
    return;
  }
  // Iterate throught linked list, searching for the correct address to free, and freeing it and removing it's node if it exists 
  while (currNode != NULL){
    currNode = currNode->next;
    if (currNode->data->addr == addr){
      prevNode->next = currNode->next;
      free(currNode->data->addr);
      free(currNode->data);
      free(currNode);
      return;
    }
    prevNode = currNode;
  }

}

//this function returns the total number of bytes currently reserved in all blocks of the heap parameter
int   mh_count(HeapType *heap){
  BlockNode *currNode = heap->head;
  int total = 0;

  // Iterate until the end of the linked list is reached, counting the elements
  while (currNode != NULL){
    total += currNode->data->size;
    currNode = currNode->next;
  }
	return total;
}

// prints to the screen information about every block in the heap parameter 
void  mh_dump(HeapType *heap){
  BlockNode *currNode = heap->head;
  while (currNode != NULL){
			printf("\t%10s: \t %d bytes stored at %p\n",currNode->data->tag,currNode->data->size,currNode->data->addr );
      currNode = currNode->next;
	}
}

//using free, this function deallocates all memory tracked in the blocks array of the heap parameter
void  mh_collect(HeapType *heap){
  BlockNode *temp = heap->head;

  // Iterate through the linked list, freeing every element we go through
  while (heap->head != NULL){
    temp = heap->head->next;
    free (heap->head->data->addr);
    free (heap->head->data);
    free (heap->head);
    heap->head = temp;
  }
}