#define _CRT_SECURE_NO_WARNINGS

#include "scanner.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//secondary functions

//Convert string to struct SCAN_INFO
struct SCAN_INFO* get_rec(char *csv_line){
	SCAN_INFO *tmp = (SCAN_INFO* ) malloc(sizeof(SCAN_INFO));
	char buf[256];
	size_t k, i = 0, field = 0, str_size = strlen(csv_line);

	//Create struct
	while (field < 7){
		//Read text to ";"-symbol and write to SCAN_INFO
		k = 0;
		//Read text to ";"-symbol and write to SCAN_INFO
		while ((i < str_size) && (csv_line[i] != ';')){
			buf[k] = csv_line[i]; 
			k++;
			i++;
		}
		//Skip ;-symbol
		i++;
		//Add null-terminated symbol
		buf[k] = '\0';
		switch (field){
			case 0:	{
				strcpy(tmp -> manufacturer, buf);
				break;
			}
			case 1:{
				strcpy(tmp -> model, buf);
				break;
			}
			case 2:{
				tmp -> year = atoi(buf);
				break;
			}
			case 3:{
				tmp -> price = (float)atof(buf);
				break;
			}
			case 4:{
				tmp -> x_size = atoi(buf);
				break;
			}
			case 5:{
				tmp -> y_size = atoi(buf);
				break;
			}
			case 6:{
				tmp -> optr = atoi(buf);
			}
		}
		field++;
	}
	return tmp;
}

//main functions

/*Check if element appear in file and if isn,t add it in file.
 *If element appear then return -4.
 *If filecan`t create then return -1.
 *True worked function return nonnegative number.
 */
int add_elem(char *ext_file_name, SCAN_INFO *element){
	FILE *dba;
	int size = -1;
	if ((dba = fopen(ext_file_name, "r+b")) == NULL)
		if ((dba = fopen(ext_file_name, "w+b")) == NULL)
			return ERROR_CREATE_FILE;
	fread(&size, sizeof(int), 1, dba);
	if (size == -1){
		//Empty file
		size++;
		fwrite(&size, sizeof(int), 1, dba);
		fwrite(element, sizeof(SCAN_INFO), 1, dba);
		fclose(dba);
		return NO_ERROR;
	}
	else{
		int i;
		SCAN_INFO *buf = (SCAN_INFO *)malloc(sizeof(SCAN_INFO));
		for (i = 0; i <= size; i++)
			if (fread(buf, sizeof(SCAN_INFO), 1 ,dba) >= 0)
				if ((strcmp(buf -> manufacturer, element -> manufacturer) == 0)
					&& (strcmp(buf -> model, element -> model) == 0))
						return ERROR_PARAMETER;
		//If this element isn't appear then write it
		size++;
		fseek(dba, sizeof(int) + sizeof(SCAN_INFO) * size, SEEK_SET);
		fwrite(element, sizeof(SCAN_INFO), 1, dba);
		rewind(dba);
		fwrite(&size, sizeof(int), 1, dba);
		fclose(dba);
		return NO_ERROR;
	}
}


//get csv file name and create ".dba" file 
int create_dba(char *csv_name){
	FILE *csv;
	FILE *dba;
	//File names with extension
	char ext_csv_name[256];
	char ext_dba_name[256];
	char *buf = (char* )malloc(256 * sizeof(char));

	strcpy(ext_csv_name, csv_name);
	strcpy(ext_dba_name, csv_name);
	strcat(ext_csv_name, ".csv");
	strcat(ext_dba_name, ".dba");
	//Open .csv file and create new .dba file
	if ((csv = fopen(ext_csv_name, "rt")) == NULL)
		return ERROR_WRITE_FILE;
	if ((dba = fopen(ext_dba_name, "w+b")) == NULL)
		return ERROR_CREATE_FILE;
	//Read line, create SCAN_INFO structure and write to .dba file
	fclose(dba);
	buf = fgets(buf, 256, csv);
	while (buf){
		if (add_elem(ext_dba_name, get_rec(buf)) != 0)
			return ERROR_PARAMETER;
		buf = fgets(buf, 256, csv);
	}
	free(buf);
	return NO_ERROR;
}


/*make ".idx" file with index, which sorting ".dba" file on names
 *@@EXAMPLE@@: 
 *".dba":
 *	0.HP;JetScan7;2007;959.99;210;297;300
 *	1.ASUS;AsScan9;2009;299.99;210;297;100
 *	2.HP;LaserScan9;2009;959.99;210;297;100
 *	3.ASUS;AsScan7;2007;999.99;210;297;300
 *	4.Dell;DellScan1;2006;999.99;210;297;200
 *	5.Dell;DellScan2;2005;999.99;210;297;150
 *".idx":
 *		3  1  4   5  0  2 */
int make_index(char *dba_name, char *field_name){
	FILE *dba;
	char ext_dba_name[256];
	strcpy(ext_dba_name, dba_name);
	strcat(ext_dba_name, ".dba");
	if ((dba = fopen(ext_dba_name, "rb")) == NULL)
		return ERROR_READ_FILE;
	//Check if field is apear
	if ((strcmp(field_name, "manufacturer") == 0)
		|| (strcmp(field_name, "year") == 0)
		|| (strcmp(field_name, "price") == 0)
		|| (strcmp(field_name, "optr") == 0)){
		//
		int i, k, size = 0;
		RECORD_SET *idx_mas = NULL; 
		RECORD_SET buf;
		FILE *idx;
		char ext_idx_name[256];
		fread(&size, sizeof(int), 1, dba);
		idx_mas = (RECORD_SET* )malloc((size + 1) * sizeof(RECORD_SET));
		//Read dba file and write data to idx_mas
		for (i = 0; i <= size; i++){
			idx_mas[i].recs = (SCAN_INFO* )malloc(sizeof(SCAN_INFO));
			fread(idx_mas[i].recs, sizeof(SCAN_INFO), 1, dba);
			idx_mas[i].rec_nmb = i;
		}
		if (strcmp(field_name, "manufacturer") == 0){
			char name_1_elem[256];
			char name_2_elem[256];
			//Sorting by manufacturer and model
			for (i = 0; i < size; i++){
				strcpy(name_1_elem, idx_mas[i].recs -> manufacturer);
				strcat(name_1_elem, idx_mas[i].recs -> model);
				for (k = i + 1; k <= size; k++){
					strcpy(name_2_elem, idx_mas[k].recs -> manufacturer);
					strcat(name_2_elem, idx_mas[k].recs -> model);
					if (strcmp(name_2_elem, name_1_elem) < 0){
						//Swap elements
						buf = idx_mas[i];
						idx_mas[i] = idx_mas[k];
						idx_mas[k] = buf;
						strcpy(name_1_elem, name_2_elem);
					}
				}
			}
		}
		else if (strcmp(field_name, "year") == 0){
			//Sorting by year
			for (i = 0; i < size; i++)
				for (k = i + 1; k <= size; k++)
					if (idx_mas[i].recs -> year > idx_mas[k].recs -> year){
						buf = idx_mas[i];
						idx_mas[i] = idx_mas[k];
						idx_mas[k] = buf;
					}
		}
		else if (strcmp(field_name, "price") == 0){
			//Sorting by price
			for (i = 0; i < size; i++)
				for (k = i + 1; k <= size; k++)
					if (idx_mas[i].recs -> price > idx_mas[k].recs -> price){
						buf = idx_mas[i];
						idx_mas[i] = idx_mas[k];
						idx_mas[k] = buf;
					}
		}
		else if (strcmp(field_name, "optr") == 0){
			//Sorting by optical resolution
			for (i = 0; i < size; i++)
				for (k = i + 1; k <= size; k++)
					if (idx_mas[i].recs -> optr > idx_mas[k].recs -> optr){
						buf = idx_mas[i];
						idx_mas[i] = idx_mas[k];
						idx_mas[k] = buf;
					}
		}
		//Create idx file name: the name of dba file + _field + .idx
		//Write result in idx file
		strcpy(ext_idx_name, dba_name);
		strcat(ext_idx_name, "_");
		strcat(ext_idx_name, field_name);
		strcat(ext_idx_name, ".idx");
		idx = fopen(ext_idx_name, "wt");
		for (i = 0; i <= size; ++i)
			fprintf(idx, "%d ", idx_mas[i].rec_nmb);
		fclose(idx);
		fclose(dba);
		return NO_ERROR;
	}
	else 
		return ERROR_PARAMETER;//error
}

//return pointer to set of records (".idx" file)
RECORD_SET* get_recs_by_index(char *dba_name, char *indx_field){
	FILE *dba;
	FILE *idx;
	char ext_dba_name[256];
	char ext_idx_name[256];
	RECORD_SET *tmp = NULL;
	int i, size = 0;

	strcpy(ext_dba_name, dba_name);
	strcat(ext_dba_name, ".dba");
	if ((dba = fopen(ext_dba_name, "rb")) == NULL)
		return NULL;//error
	reindex(dba_name);
	strcpy(ext_idx_name, dba_name);
	strcat(ext_idx_name, "_");
	strcat(ext_idx_name, indx_field);
	strcat(ext_idx_name, ".idx");
	if ((idx = fopen(ext_idx_name, "rt")) == NULL)
		return NULL;//error
	fread(&size, sizeof(int), 1, dba);
	tmp = (RECORD_SET* )malloc((size + 1) * sizeof(RECORD_SET));
	for (i = 0; i <= size; i++){
		//Read ".idx" file, go to position in ".dba" file and read scanner data
		tmp[i].rec_nmb = fgetc(idx) - 48; // -49 because fgets return number of symblol on ASCII
		fgetc(idx);
		fseek(dba, sizeof(int) + sizeof(SCAN_INFO) * (tmp[i].rec_nmb), SEEK_SET);
		tmp[i].recs = (SCAN_INFO* ) malloc(sizeof(SCAN_INFO));
		fread(tmp[i].recs, sizeof(SCAN_INFO), 1, dba);
	}
	return tmp;
}

//create index files with all fields in struct SCAN_INFO
void reindex(char *dba_name){
	if ((make_index(dba_name, "manufacturer")!= 0) 
		|| (make_index(dba_name, "year")!= 0)
		|| (make_index(dba_name, "price")!= 0)
		|| (make_index(dba_name, "optr")!= 0))
		return;
}

//delete element n in ".dba" file and after that call reindex()
int del_scan(char *dba_name, int n){
	FILE *dba;
	int i, size = 0;
	SCAN_INFO *buf = (SCAN_INFO *)malloc(sizeof(SCAN_INFO));
	char ext_dba_name[256];

	strcpy(ext_dba_name, dba_name);
	strcat(ext_dba_name, ".dba");
	if ((dba = fopen(ext_dba_name, "r+b")) == NULL)
		return ERROR_READ_FILE;//error
	fread(&size, sizeof(int), 1, dba);
	if (size < n) 
		return ERROR_PARAMETER; //error
	// Shift elements
	for (i = n; i < size; i++){
		fseek(dba, sizeof(int) + (i + 1) * sizeof(SCAN_INFO), SEEK_SET);
		fread(buf, sizeof(SCAN_INFO), 1, dba);
		fseek(dba, sizeof(int) + i * sizeof(SCAN_INFO), SEEK_SET);
		fwrite(buf, sizeof(SCAN_INFO), 1, dba);
	}
	rewind(dba);
	size--;
	fwrite(&size, sizeof(int), 1, dba);
	fclose(dba);
	reindex(dba_name);
	return NO_ERROR;
}

//read data in ".dba" file and create ".txt" file where 
void create_txt(char *dba_name, float price){
	char flag = 'F'; // Flag, if find elements
	int i, k, size;
	FILE *txt;
	RECORD_SET *price_arr = NULL;
	char ext_txt_name[256];
	strcpy(ext_txt_name, dba_name);
	strcat(ext_txt_name, "_price.txt");
	txt = fopen(ext_txt_name, "w+t");
	price_arr = get_recs_by_index(dba_name, "price");
	size = _msize(price_arr)/sizeof(RECORD_SET);
	size--;
	//Search
	for (i = size; i >= 0; i--)
		if (price_arr[i].recs -> price <= price){
			flag = 'T';
			break;
		}
	//If elements is appear then write it in txt, if not - write massage
	if (flag == 'F')
		fprintf(txt, "Scanners with this parametres isn't find");
	else
		//Write in txt
		for (k = 0; k <= i; k++){
			fprintf(txt, "*------------------------------------------------*\n");
			fprintf(txt, "*  %d. %s %s\n", k + 1, price_arr[k].recs -> manufacturer, price_arr[k].recs -> model);
			fprintf(txt, "*  Year: %d\n", price_arr[k].recs -> year);
			fprintf(txt, "*  Price: %0.2f\n", price_arr[k].recs -> price);
			fprintf(txt, "*  Size: %d x %d\n", price_arr[k].recs -> x_size, price_arr[k].recs -> y_size);
			fprintf(txt, "*  Optr: %d\n", price_arr[k].recs -> optr);
			fprintf(txt, "*------------------------------------------------*\n\n");
		}
	fclose(txt);
}