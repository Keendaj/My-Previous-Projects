#include <stdlib.h>
#include "SorLib.h"
#include <math.h>

void InsertSort(int array[], int size) {
	int newElement, location;
	
	for (int i = 1; i < size; i++)
	{
		newElement = array[i];
		location = i - 1;
		while (location >= 0 && array[location] > newElement)
		{
			array[location + 1] = array[location];
			location--;
		}
		array[location + 1] = newElement;
	}
}


int* GeneratePrattSequence(int* size) {
	int counter = 0;
	int i = 0;
	int j = 0;
	int k = 1;
	int* array = malloc(sizeof(int) * k);
	int* phelp;
	while (pow(2, counter) < *size) {
		counter++;
	}
	for (i = 0; i + j < counter; i++)
	{
		for (; i + j < counter; j++) {
			int num = pow(2, i) * pow(3, j);
			if (num >= *size) {
				continue;
			}
			phelp = realloc(array, sizeof(int) * k);
			array = phelp;
			array[k - 1] = num;
			k++;
		}
		j = 0;
	}
	*size = k - 1;
	InsertSort(array, k - 1);
	return array;
}

void ShellSortBasic(int* array, int size) {
	int step = size / 2;
	int* testarray;
	int start = 0;
	int j;
	int counter = 0;
	while (step != 0) {
		testarray = malloc(sizeof(int) * (size / step));
		for (int i = 0; i < step; i++) {
			j = start;
			while (j < size) {
				testarray[counter] = array[j];
				j += step;
				counter++;
			}
			InsertSort(testarray, (size / step));
			j = start;
			counter = 0;
			while (j < size) {
				array[j] = testarray[counter];
				j += step;
				counter++;
			}
			start++;
			counter = 0;
		}
		free(testarray);
		start = 0;
		step /= 2;
	}
}

void ShellSortSecond(int* array, int size) {
	int step = size * 5;
	step /= 11;
	int k = 0;
	int* testarray;
	int start = 0;
	int j;
	int counter = 0;
	while (step > 0) {
		if (step > size) {
			k++;
			continue;
		}
		testarray = malloc(sizeof(int) * (size / step +1));
		for (int i = 0; i < step; i++) {
			j = start;
			while (j < size) {
				testarray[counter] = array[j];
				j += step;
				counter++;
			}
			InsertSort(testarray, (size / step));
			j = start;
			counter = 0;
			while (j < size) {
				array[j] = testarray[counter];
				j += step;
				counter++;
			}
			start++;
			counter = 0;
		}
		free(testarray);
		start = 0;
		step *= 5;
		step /= 11;
	}
}

void ShellSortHibb(int* array, int size) {
	int k = log2(size + 1);
	int step = pow(2, k) - 1;
	int* testarray;
	int start = 0;
	int j;
	int counter = 0;
	while (step > 0) {
		testarray = malloc(sizeof(int) * (size / step));
		for (int i = 0; i < step; i++) {
			j = start;
			while (j < size) {
				testarray[counter] = array[j];
				j += step;
				counter++;
			}
			InsertSort(testarray, (size / step));
			j = start;
			counter = 0;
			while (j < size) {
				array[j] = testarray[counter];
				j += step;
				counter++;
			}
			start++;
			counter = 0;
		}
		free(testarray);
		start = 0;
		k--;
		step = pow(2, k) - 1;
	}
}

void ShellSortSedg(int* array, int size) {
	int k = log2(1.5 / 2 + sqrt(2.25-4+4*size) / 2);
	int step = pow(4,k) + pow(3, k - 1) + 1;
	int* testarray;
	int start = 0;
	int j;
	int counter = 0;
	while (step > 0) {
		testarray = malloc(sizeof(int) * (size / step));
		for (int i = 0; i < step; i++) {
			j = start;
			while (j < size) {
				testarray[counter] = array[j];
				j += step;
				counter++;
			}
			InsertSort(testarray, (size / step));
			j = start;
			counter = 0;
			while (j < size) {
				array[j] = testarray[counter];
				j += step;
				counter++;
			}
			start++;
			counter = 0;
		}
		free(testarray);
		start = 0;
		k--;
		if(k > 0){
			step = pow(4, k) + pow(3, k - 1) + 1;
			
		}
		else if(k==0){
			step = 1;
		}
		else {
			break;
		}
		
	}
}

void ShellSortEmp(int* array, int size) {
	int maxnum = 701;
	int count = 9;
	int Test[9] = {701,301,132,57,23,10,4,1,0 };
	while (size > maxnum) {
		maxnum *= 2.25;
		count++;
	}
	int *Steps = malloc(sizeof(int)*count);
	for(int i = 0; i<count-9;i++){
		Steps[i] = maxnum;
		maxnum /= 2.25;
	}
	for (int i = count - 9; i < count; i++) {
		Steps[i] = Test[i - count + 9];
	}
	int k = 0;
	int* testarray;
	int start = 0;
	int j;
	int counter = 0;
	while (Steps[k] > 0) {
		if (Steps[k] > size) {
			k++;
			continue;
		}
		testarray = malloc(sizeof(int) * (size / Steps[k]));
		for (int i = 0; i < Steps[k]; i++) {
			j = start;
			while (j < size) {
				testarray[counter] = array[j];
				j += Steps[k];
				counter++;
			}
			InsertSort(testarray, (size / Steps[k]));
			j = start;
			counter = 0;
			while (j < size) {
				array[j] = testarray[counter];
				j += Steps[k];
				counter++;
			}
			start++;
			counter = 0;
		}
		free(testarray);
		start = 0;
		k++;
	}
}

void ShellSortPratt(int* array, int size) {
	int SequenceSize = size;
	int *PrattSequence = GeneratePrattSequence(&SequenceSize);
	int k = SequenceSize-1;
	int* testarray;
	int start = 0;
	int j;
	int counter = 0;
	while (k >= 0) {
		testarray = malloc(sizeof(int) * (size / PrattSequence[k] + 1));
		for (int i = 0; i < PrattSequence[k]; i++) {
			j = start;
			while (j < size) {
				testarray[counter] = array[j];
				j += PrattSequence[k];
				counter++;
			}
			InsertSort(testarray, (size / PrattSequence[k]));
			j = start;
			counter = 0;
			while (j < size) {
				array[j] = testarray[counter];
				j += PrattSequence[k];
				counter++;
			}
			start++;
			counter = 0;
		}
		free(testarray);
		start = 0;
		k--;
	}
}

__declspec(dllexport) sort_info_t *GetSortList(int* count) {
	sort_info_t sort_list[6] = {{ShellSortBasic,SORT_SHELL, SORT_SUBQUADRATIC,"Basic shell sort"},
		{ShellSortSecond,SORT_SHELL,SORT_SUBQUADRATIC, "Shell sort with gap 5/11"},
		{ShellSortHibb, SORT_SHELL,SORT_SUBQUADRATIC,"Hibbard sort"},
		{ShellSortSedg, SORT_SHELL, SORT_SUBQUADRATIC, "Sedgewick sort"},
		{ShellSortEmp, SORT_SHELL, SORT_SUBQUADRATIC, "Empiric sort"},
		{ShellSortPratt, SORT_SHELL, SORT_SUBQUADRATIC, "Pratt sort"}};
	*count = 6;
	return sort_list;
}