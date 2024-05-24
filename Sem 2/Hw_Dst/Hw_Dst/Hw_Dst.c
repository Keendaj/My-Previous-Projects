#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
#pragma warning(disable:4996)

int Is_space(char sym) {
	if (!((sym>='a'&&sym<='z')||(sym >= 'A' && sym <= 'Z')||(sym<='9'&&sym>='0'))) {
		return 1;
	}
	return 0;//Заменить на проверку на не буквы и не цифры
}


char* Realloc_s(char* arr, int size) {
	char* new_arr = realloc(arr, size);
	if (new_arr == NULL) {
		return NULL;
	}
	return new_arr;//Путём невероятного анализа была выяснено, что realloc в C11 сам освобождает память
}

char* ConvertToArr(char* buffer,int width, int* buffer_counter,int* size,char* arr, char sym) {
	for (int j = 0; j < buffer_counter[0]; j++) {
		arr = Realloc_s(arr, sizeof(char) * (size[0] + 1));
		if (arr == NULL) {
			return NULL;
		}
		arr[size[0]] = buffer[j];
		size[0]++;
	}
	if ((size >= width || sym == ' ')&&buffer_counter[0]!=0) {

		arr = Realloc_s(arr, sizeof(char) * (size[0] + 1));
		if (arr == NULL) {
			return NULL;
		}
		arr[size[0]] = sym;
		size[0]++;
	}
	buffer_counter[0] = 0;
	return arr;
}
void ClearBuffer(int counter,char** arr) {
	for (int i = 0; i < counter + 1; i++) {
		free(arr[i]);
	}
	free(arr);
}
char* ReadParagraph() {
	char** arr = malloc(sizeof(char*));
	char s;
	int i = 0, counter;
	getchar();
	arr[i] = malloc(sizeof(char));
	do{
		counter = 0;
		arr = Realloc_s(arr, sizeof(arr) * (i + 1));
		if (arr == NULL) {
			return NULL;
		}
		arr[i] = malloc(sizeof(char));
		do{//Считывание строки
			s = getchar();
			arr[i] = Realloc_s(arr[i], sizeof(char) * (counter + 1));
			if (arr == NULL) {
				return NULL;
			}
			arr[i][counter] = s;
			counter++;
		} while (s != '\n');
		i++;//Переход на новую строку
	} while (arr[i - 1][0] != '\n');
	return arr;
}


void Print(char const **arr){
	int i = 0, counter;
	while (arr[i][0] != '\n')
	{
		counter = 0;
		while (arr[i][counter] != '\n')
		{
			printf("%c", arr[i][counter]);
			counter++;
		}
		i++;
		printf("\n");
	}
	printf("\n");
}

char **Text_Wrap(char **arr, int width) { 
	char** res_arr = malloc(sizeof(char*));
	int prev_arr_counter = 0,new_arr_counter = 0, counter, size = 0, is_prev_space = 0, buffer_counter = 0, end = 0;
	char space = ' ',new_string = '\n';
	char* buffer = malloc(sizeof(char)*(width+1));
	
	while (arr[prev_arr_counter][0] != '\n') {
		counter = 0;
		if (1 - end) {
			size = 0;
			end = 0;
			res_arr = Realloc_s(res_arr, sizeof(res_arr) * (new_arr_counter + 1));
			if (res_arr == NULL) {
				ClearBuffer(new_arr_counter, res_arr);
				free(buffer);
				return NULL;
			}
			res_arr[new_arr_counter] = malloc(sizeof(char) * (size + 1));
		}
		while (arr[prev_arr_counter][counter]!='\n') {
			if (is_prev_space && Is_space(arr[prev_arr_counter][counter])) {
				counter++;
				continue;
			}
			if (Is_space(arr[prev_arr_counter][counter])) {
				is_prev_space = 1;
				if (counter == 0) {
					continue;
				}
				if (size + buffer_counter <= width) {
					res_arr[new_arr_counter] = ConvertToArr(buffer, width, &buffer_counter, &size, res_arr[new_arr_counter], space);
					if (size == NULL) {
						ClearBuffer(new_arr_counter, res_arr);
						free(buffer);
						return NULL;
					}
				}
				else {
					res_arr[new_arr_counter][size] = '\n';
					new_arr_counter++;
					size = 0;
					res_arr = Realloc_s(res_arr, sizeof(res_arr) * (new_arr_counter + 1));
					res_arr[new_arr_counter] = malloc(sizeof(char) * (size+1));
					if (buffer_counter > width || res_arr == NULL) {
						ClearBuffer(new_arr_counter, res_arr);
						free(buffer);
						return NULL;
					}
					else {
						res_arr[new_arr_counter] = ConvertToArr(buffer, width, &buffer_counter, &size, res_arr[new_arr_counter], space);
					}
				}
				
			}
			else {
				is_prev_space = 0;

				buffer[buffer_counter] = arr[prev_arr_counter][counter];

				buffer_counter++;
				if (buffer_counter > width) {
					ClearBuffer(new_arr_counter, res_arr);
					free(buffer);
					return NULL;
				}
			}		
			counter++;
		}
		if (size + buffer_counter <= width) {
			res_arr[new_arr_counter] = ConvertToArr(buffer, width, &buffer_counter, &size, res_arr[new_arr_counter],space);
			if (size == NULL) {
				ClearBuffer(new_arr_counter, res_arr);
				free(buffer);
				return NULL;
			}
			if (size >= width) {
				res_arr[new_arr_counter][size - 1] = '\n';
				new_arr_counter++;
				res_arr = Realloc_s(res_arr, sizeof(res_arr) * (new_arr_counter + 1));
				res_arr[new_arr_counter] = malloc(sizeof(char) * (size + 1));
				size = 0;
				if (res_arr == NULL) {
					ClearBuffer(new_arr_counter, res_arr);
					free(buffer);
					return NULL;
				}
			}
			else {
				end = 1;
			}
		}
		else {
			res_arr[new_arr_counter][size-1] = '\n';
			new_arr_counter++;
			size = 0;
			res_arr = Realloc_s(res_arr, sizeof(res_arr) * (new_arr_counter + 1));
			res_arr[new_arr_counter] = malloc(sizeof(char) * (size + 1));
			if (buffer_counter > width || res_arr == NULL) {
				ClearBuffer(new_arr_counter, res_arr);
				free(buffer);
				return NULL;
			}
			else {
				res_arr[new_arr_counter] = ConvertToArr(buffer, width, &buffer_counter, &size, res_arr[new_arr_counter], space);
				if (size >= width) {
					res_arr[new_arr_counter][size - 1] = '\n';
					new_arr_counter++;
					size = 0;
					res_arr = Realloc_s(res_arr, sizeof(res_arr) * (new_arr_counter + 1));
					res_arr[new_arr_counter] = malloc(sizeof(char) * (size + 1));
					if (res_arr == NULL) {
						ClearBuffer(new_arr_counter, res_arr);
						free(buffer);
						return NULL;
					}
				}
				else {
					end = 1;
				}
			}
		}
		prev_arr_counter++;
	}
	res_arr[new_arr_counter][size] = '\n';
	res_arr = Realloc_s(res_arr, sizeof(res_arr) * (new_arr_counter + 2));
	res_arr[new_arr_counter+1] = malloc(sizeof(char));
	if (res_arr == NULL) {
		ClearBuffer(new_arr_counter, res_arr);
		free(buffer);
		return NULL;
	}
	res_arr[new_arr_counter+1][0] = '\n';
	free(buffer);
	return res_arr;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int width;
	do {
		printf("Введите ширину строки: ");
		scanf("%d", &width);
		printf("Введите исходный абзац: \n");
		char** arr = ReadParagraph();
		if (arr[0][0] == '\n') {
			return 0;
		}
		Print(arr);
		char** res_arr = Text_Wrap(arr, width);
		if (res_arr == NULL) {
			printf("Вы ввели слово больше заданной ширины");

			return 1;
		}
		Print(res_arr);
	} while (1);
}