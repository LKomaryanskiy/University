/***********************************
* file: mem_dispatcher.h
* written: 11/26/2015
* last modified: 12/07/2015
* synopsis: memory dispatcher interface
* autor: Leonid Komaryanskiy
************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 10

typedef  enum {FREE, ALLOCATED} STATUS;

typedef struct chunk{
	size_t id;
	size_t size;
	STATUS status;
	struct chunk* next;//pointer to the next memory block
} mem_list;
 
typedef struct {
	int last_id_used;
	mem_list *first; //pointer to the first memory block
} mem_dispatcher;


//creates a heap as a single free block  with id 0 and HEAP_SIZE size
void init(mem_dispatcher *md);

//returns block id if allocated and -1 otherwise
int allocate(mem_dispatcher *md, size_t size);

//returns nonnegative value if block is deallocated and -1 otherwise
int deallocate(mem_dispatcher *md, size_t block_id);

//reunites free blocks that were previously stored in various parts of a heap //into one successive block 
void defragment(mem_dispatcher *md);

//displays heap status
void show_memory_map(mem_dispatcher *md);

//list destructor
void delete_list(mem_list *pointer);