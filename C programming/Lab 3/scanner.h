/***********************************
* file: scanner.h
* written: 12/07/2015
* last modified: 12/17/2015
* synopsis: this program work with scanner data files 
* autor: Leonid Komaryanskiy
************************************/
#define _CRT_SECURE_NO_WARNINGS
#pragma once

//Errors
#define ERROR_PARAMETER -4
#define ERROR_WRITE_FILE -3
#define ERROR_READ_FILE -2
#define ERROR_CREATE_FILE -1
#define NO_ERROR 0

//scanner data
typedef struct {
	char manufacturer[127];
	char model[128];
	int year;	 
	float price;
	int x_size;
	int y_size;
	int optr; 
} SCAN_INFO;

typedef struct{
	int rec_nmb;	//number of records
	SCAN_INFO *recs;//records 
}RECORD_SET;


//get csv file name and create ".dba" file 
int create_dba(char *csv_file);

/*Check if element appear in file and if isn,t add it in file.
 *If element appear then return -1.
 *If file can`t open to rewrite or can`t create then return -2.
 *True wroked function return nonnegative number.
 */
int add_elem(char *file_name ,SCAN_INFO *element);

//Convert string to struct SCAN_INFO
struct SCAN_INFO* get_rec(char *csv_line);

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
int make_index(char *dba, char *field_name);

//return pointer to set of records (".idx" file)
RECORD_SET* get_recs_by_index(char *dba , char *indx_field );

//create index files with all fields in struct SCAN_INFO
void reindex(char *dba);

//delete element n in ".dba" file and after that call reindex()
int del_scan(char *dba, int n);

//read data in ".dba" file and create ".txt" file where 
void create_txt(char *dba, float price);