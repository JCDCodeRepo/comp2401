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

  HeapType *heap2;																		// The second heap on which we will do the additional testing.
  heap2 = (HeapType *) malloc(sizeof(HeapType));

  mh_init(heap2);

  void  *ptr5, *ptr6, *ptr7, *ptr8, *ptr9;						// These will point to the five additional data types we will be testing

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

//this function initializes the heap variable declared in main, including the dynamic allocation of the maximum number of blocks
void  mh_init(HeapType *heap){
	heap->numBlocks = 0;
	heap->blocks = (BlockType *) malloc((MAX_BLK) * sizeof(BlockType));
}

//this function frees the memory allocated for all the blocks in the heap parameter
void  mh_cleanup(HeapType *heap){
	free(heap->blocks);
}

/*
using malloc , this function dynamically allocates a new block of memory of size n bytes 
adds the new block of memory as the next element of the blocks array in the heap parameter
saves the address of the new memory in that blocks element , as well as its size and a user-defined label to indicate the use for this block, and it sets the block s element to reserved 
itreturns the pointer returned by malloc
*/
void* mh_alloc(HeapType *heap, int n, char *label){
	void *newBlock = (void *) malloc(n);
	heap->blocks[heap->numBlocks].addr = newBlock;
	heap->blocks[heap->numBlocks].size = n;
	strcpy(heap->blocks[heap->numBlocks].tag, label);
	heap->blocks[heap->numBlocks].rsv = C_TRUE;
	heap->numBlocks++;
	return newBlock;
}

/*
finds the blocks element in the heap parameter that corresponds to the block of memory pointed to by addr 
sets the blocks element to not reserved and deallocates th e memory pointed to by addr using free
*/
void  mh_dealloc(HeapType *heap, void *addr){
	int i;
	for(i = 0; i < heap->numBlocks; i++){
		if (heap->blocks[i].addr == addr){
			heap->blocks[i].rsv = C_FALSE;
			free(heap->blocks[i].addr);
		}
	}
}

//this function returns the total number of bytes currently reserved in all blocks of the heap parameter
int   mh_count(HeapType *heap){
	int total = 0;
	int i;
	for(i = 0; i < heap->numBlocks; i++){
		if (heap->blocks[i].rsv == C_TRUE){
			total += heap->blocks[i].size;
		}
	}
	return total;
}

// prints to the screen information about every block in the heap parameter 
void  mh_dump(HeapType *heap){
	int i;
	for(i = 0; i < heap->numBlocks; i++){
		if (heap->blocks[i].rsv == C_TRUE ){
			printf("\t%10s: \t %d bytes stored at %p\n",heap->blocks[i].tag,heap->blocks[i].size,heap->blocks[i].addr );
		}
	}
}

//using free , this function deallocates all memory tracked in the blocks array of the heap parameter
void  mh_collect(HeapType *heap){
	int i;
	for(i = 0; i < heap->numBlocks; i++)
		if (heap->blocks[i].rsv == C_TRUE ){
			heap->blocks[i].rsv = C_FALSE;
			heap->blocks[i].size = 0;
			free(heap->blocks[i].addr);
		}
}