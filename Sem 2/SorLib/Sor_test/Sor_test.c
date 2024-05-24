#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SorLib.h"
#include <Windows.h>
#include <time.h>
#define MIN_SIZE 10
#define MAX_SIZE 10000
#define STEP_SIZE 10
#define REPEAT_COUNT 10

typedef sort_info_t *(*GetListFunc)(int* count);

int Random(double a, double b) {
	double s = rand();
	s /= RAND_MAX + 1;
	s *= b - a;
	s += a;
	return s;
}

int compare(const void* a, const void* b)
{
	int data1 = *(int*)a, data2 = *(int*)b;
	if (data1 < data2) 
		return -1;
	else if (data1 == data2) 
		return 0;
	else
		return 1;
}

void CopyArray(int *dst, int *src, int size) {
	for (int i = 0; i < size;i++) {
		dst[i] = src[i];
	}
}

int main(){

	HMODULE Lib = LoadLibrary(TEXT("../x64/Debug/SorLib.dll"));
	if (Lib == NULL) {
		return 1;
	}
	GetListFunc MyFunc = (GetListFunc)GetProcAddress(Lib, "GetSortList");
	int count = 0;
	sort_info_t *List;
	List = MyFunc(&count);
	
	for (int i = MIN_SIZE; i < MAX_SIZE; i += STEP_SIZE) {
 		int* arr1 = malloc(sizeof(int*) * i);
		for (int k = 0; k < i; k++) {
			arr1[k] = Random(-1000000,100000);
		}
		int *arr2 = (int *)malloc(sizeof(int) * i), * arr3 = (int*)malloc(sizeof(int) * i);
		CopyArray(arr2, arr1, i);
		
		qsort(arr2, i, sizeof(int), compare);

		for (int k = 0; k < count; k++) {
			CopyArray(arr3, arr1, i);
			List[k].sort(arr3,i);
			for (int j = 0; j < i; j++) {
				if (arr2[j] != arr3[j]) {
					printf("Ошибка при размере массива: %d и сортировке: %s \n",i,List[k].name);
				}
			}

		}






		free(arr1);
		free(arr2);
	}
	
	FreeLibrary(Lib);
	return 0;
}