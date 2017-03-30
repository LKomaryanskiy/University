#define _CRT_SECURE_NO_WARNINGS
#include "scanner.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	create_dba("data");
	reindex("data");
	//del_scan("data", 2);
	create_txt("data", 960);
	printf("DONE! \n");
	system("pause");
	return 0;
}