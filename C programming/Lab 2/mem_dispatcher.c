#include "mem_dispatcher.h"


//creates a heap as a single free block  with id 0 and HEAP_SIZE size
void init(mem_dispatcher *md){
	mem_list *temp = malloc(sizeof(mem_list));
	md -> last_id_used = temp -> id = 1;
	temp -> size = HEAP_SIZE;
	temp -> status = FREE;
	temp -> next = NULL;
	md -> first = temp;
}

//get pointer on list head and delete element which needed
void delete_elem(mem_dispatcher *md, mem_list **element){
	mem_list *buf = md -> first;
	//Search element which need to delete
	while (buf -> next != (*element))
		buf = buf -> next;
	buf -> next = buf -> next -> next;
	free((*element));
	(*element) = buf;
}

//returns block id if allocated and -1 otherwise
int allocate(mem_dispatcher *md, size_t size){
	mem_list *buf = md -> first;
	//Search free element with size which we needed
	while (buf != NULL){
		if ((buf -> status == FREE) && (buf -> size >= size)){
			/*If free block size is equal to block size which we need to allocate
			then we change his status to ALLOCATED*/
			if (buf -> size == size){
				buf -> status = ALLOCATED;
				return buf -> id;
			}
			else{
				//Decrease block size and create new element
				mem_list *temp = malloc(sizeof(mem_list));
				(md -> last_id_used)++;
				temp -> id = md -> last_id_used;
				temp -> size = size;
				temp -> status = ALLOCATED;
				temp -> next = md -> first;
				md -> first = temp;
				buf -> size -= size;
				return temp -> id;
			}
		}
		buf = buf -> next;
	}
	//Return -1 if block isn't found
	return -1;
}

//returns nonnegative value if block is deallocated and -1 otherwise
int deallocate(mem_dispatcher *md, size_t block_id){
	mem_list *db = md -> first; // deallocate block
	//Search element which we need to deallocate
	while (db != NULL){
		if (db -> id == block_id){
			//If next elements is FREE too, then unit it in one block
			if ((db -> next != NULL) && (db -> next -> status == FREE)){
				mem_list *buf = db -> next;
				while ((buf != NULL) && (buf -> status != ALLOCATED)){
					db -> size += buf -> size;
					delete_elem(md, &buf);
					buf = buf -> next;
				}
			}
			//Change status and return 1 (no errors)
			db -> status = FREE;
			return 1;
		}
		db = db -> next;
	}
	//If element with block_id isn`t find then return -1 (error)
	return -1;
}

//reunites free blocks that were previously stored in various parts of a heap //into one successive block 
void defragment(mem_dispatcher *md){
	mem_list *first_free = md -> first;
	//Search first FREE block, where will be add other free blocks
	while ((first_free != NULL) && (first_free -> status != FREE ))
		first_free = first_free -> next;
	//Delete other free blocks and add to first free block memory
	if (first_free != NULL){
		mem_list *buf = first_free -> next;
		while (buf != NULL){
			if (buf -> status == FREE){
				first_free -> size += buf -> size;
				delete_elem(md, &buf);
			}
			buf = buf -> next;
		}
	}
}

//displays heap status
void show_memory_map(mem_dispatcher *md){
	mem_list *buf = md -> first;
	while (buf != NULL){
		printf("block id:%d\n", buf -> id);
		printf("\tsize:%d", buf -> size);
		if (buf -> status == FREE)
			printf("\t\tstatus:FREE\n");
		else
			printf("\t\tstatus:ALLOCATED\n");
		buf = buf -> next;
	}
}

//list destructor
void delete_list(mem_list *pointer){
	if (pointer != NULL)
		delete_list(pointer -> next);
	free(pointer);
}