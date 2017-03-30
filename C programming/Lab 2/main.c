#include "mem_dispatcher.h"
#include <stdio.h>


void menu(){
	system("cls");
	printf("1. Allocate\n");
	printf("2. Deallocate\n");
	printf("3. Show memory map\n");
	printf("4. Defragment\n");
	printf("5. Exit\n");
	printf("Enter command: ");
}

int main(){
	mem_dispatcher *list = malloc(sizeof(mem_dispatcher));
	int variant = 0, argument = 0;
	init(list);

	while (variant != 5){
		menu();
		argument = 0;
		scanf("%d", &variant);
		fflush(stdin);
		printf("\n");
		switch (variant){
			case 1:{
					//Allocate
					printf("Enter block size: ");
					scanf("%d", &argument);
					if (argument > 0){
						if (allocate(list, argument) > 0)
							printf("Done!\n");
						else
							printf("Can`t create block with this size!\n");
					}
					else
						printf("Wrong parameter!\n");
					break;
			}
			case 2:{
					//Deallocate
					printf("Enter block ID: ");
					scanf("%d", &argument);
					if (argument > 0){
						if (deallocate(list, argument) > 0)
							printf("Done!\n");
						else
							printf("Block with this ID isn`t found!\n");
					}
					else
						printf("Wrong parameter!\n");
					break;
			}
			case 3:{
					//Show memory map
					show_memory_map(list);
					break;
			}
			case 4:{
					//Defragment
					defragment(list);
					printf("Done!\n");
					break;
			}
			case 5:{
					//Exit
					delete_list(list -> first);
					free(list);
					exit(EXIT_SUCCESS);
			}
			default:{
					printf("Wrong command!\n");
					break;
			}
		}
		printf("\nPress any key to continue..");
		getch();
		fflush(stdin);
	}
	return 0;
}