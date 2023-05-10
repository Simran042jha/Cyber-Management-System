#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Hashtable Hashtable;
typedef struct data data;
typedef struct ArrTime ArrTime;
struct ArrTime {
	int day, mnth, yr, hr, min;
};
struct data{
	size_t id;
	char usrname[11];
	struct ArrTime arrivalTime;
	data* next;
};
struct Hashtable
{
	data** table_ptr;
	size_t size;
	size_t count;
	size_t(*insert_user)(Hashtable*, size_t, const char*, ArrTime);
	data(*search_user)(Hashtable*, size_t);
	size_t (*delete_user)(Hashtable*, size_t, int);
	int (*show)(Hashtable*);
};
Hashtable* create_hashtable(size_t);
void delete_hashtable(Hashtable*);