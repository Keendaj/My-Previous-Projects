#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define Length 10000


int Random(int a, int b) {
	float s = rand();
	s /= RAND_MAX	;
	s *= b - a;
	s += a;
	return s;
}
void Fillints(float arr[], int length, int a, int b) {
	for (int i = 0; i < length; i++) {
		int s = Random(a, b);
		arr[i] = s;
	}
}

void Printints(float arr[], int length) {
	for (int i = 0; i < length;i++) {
		printf("%.1f ", arr[i]);
	}
	printf("\n");
}
void WriteText(char const* filename, float arr[], int length) {
	FILE* myfile = fopen(filename, "w");
	for (int i = 0; i < length; i++) {
		fprintf(myfile, "%f ", arr[i]);
	}
	fclose(myfile);
}
void WriteBinary(char const* filename, int arr[], int length) {
	FILE* myfile = fopen(filename, "wb");
	fwrite(arr, sizeof(float), length, myfile);
	fclose(myfile);
}
int* ReadFile(char const* filename, int *length){
	FILE* myfile = fopen(filename, "r");
	fseek(myfile, -1023, SEEK_END);
	float *arr = malloc(sizeof(float));
	float fnum = 0;
	int len = 0;
	while (fscanf(myfile, "%f", &fnum)!=EOF) {
		len++;
		arr = realloc(arr, sizeof(float) * len);
		arr[len - 1] = fnum;
	}
	*length = len;
	fclose(myfile);
	return arr;
}
int* ReadBinary(char const* filename, int* length) {
	FILE* myfile = fopen(filename, "rb");
	int size = 1023;
	*length = size/sizeof(float);
	fseek(myfile, -1023, SEEK_END);
	float *arr = malloc(size);
	fread(arr, sizeof(float), *length, myfile);
	fclose(myfile);
	return arr;
}
void FileDump(char const* filename) {
	FILE* myfile = fopen(filename, "rb");
	unsigned char s1 = 0;
	char s2 = 0;
	int count = 0;
	fseek(myfile, -1023, SEEK_END);
	while (s2 != EOF) {
		printf("%p: ", ftell(myfile));
		for (int i = 0; i < 16; i++) {
			s2 = fgetc(myfile);
			if (s2 == EOF){
				fclose(myfile);
				return;
			}
			s1 = s2;
			printf("%02X ", s1);
		}
		printf("\n");
	}
	fclose(myfile);
}
void FileDumpPlus(char const* filename) {
	FILE* myfile = fopen(filename, "rb");
	int z, len = 16;
	fseek(myfile, 0, SEEK_END);
	int size = 1023;
	fseek(myfile, -1023, SEEK_END);
	unsigned char *arr = malloc(sizeof(unsigned char)*len);
	unsigned char s;
	while (size > 0) {
		printf("%p: ", ftell(myfile));
		if (size < len) {
			len = size;
		}
		size -= 16;
		fread(arr, sizeof(unsigned char), len, myfile);
		for (int i = 0; i < len; i++) {
			printf("%02X ", arr[i]);
			
		}
		for (int i = 16; i > len; i--) {
			printf("   ");
		}
		for (int i = 0; i < len; i++) {
			if (arr[i] == EOF) {
				break;
			}
			if (isprint(arr[i])) {
				printf("%c", arr[i]);
			}
			else {
				printf(".");
			}
		}
		
		printf("\n");
	}
	fclose(myfile);
}

int main() {
	float arr[Length], * newarrtxt, * newarrbin;
	int a = 0, b = 100, newlentxt,newlenbin;
	Fillints(arr,Length,a,b);
	WriteText("array.txt", arr, Length);
	WriteBinary("array.bin", arr, Length);
	newarrtxt =  ReadFile("array.txt", &newlentxt);
	newarrbin = ReadBinary("array.bin", &newlenbin);
	printf("\n");
	printf("Txt numbers: ");
	Printints(newarrtxt, newlentxt);
	printf("Bin numbers: ");
	Printints(newarrbin, newlenbin);
	printf("\n");
	printf("Dump");
	printf("\n");
	//FileDump("array.txt");
	printf("\n");
	printf("\n");
	//FileDump("array.bin");
	printf("\n");
	printf("\n");
	printf("DumpPlus");
	printf("\n");
	FileDumpPlus("array.txt");
	printf("\n");
	FileDumpPlus("array.bin");


	return 0;
}