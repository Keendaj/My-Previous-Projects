#include<stdio.h>
#pragma warning(disable:4996)
#include<locale.h>
#define Length 100

//Проверка на нижний регистр
int LowerCheck(int x) {
	if (x >= 'a' && x <= 'z') {
		return 1;
	}
	return 0;
}

//Преобразования всех букв в верхний регистр
void UpperCase(char str[]) {
	int x;

	for (int i = 0; i < Length; i++) {
		x = str[i];

		if (x == 0) {
			break;
		}
		else if (LowerCheck(x)) {
			str[i] = x - 'a' + 'A';
		}
	}
}
void PrintArray(char str[]) {
	for (int i = 0; i < Length; i++) {
		if (str[i] == 0){
			break;
		}
		printf("%c", str[i]);
	}
	printf("\n");
}
int main() {
	char str[Length] = "";
	int id = 1;

	setlocale(LC_CTYPE, "Russian");

	while (id != 0) {
		printf("Введите строку, которую хотите преобразовать: ");
		gets(str);

		id = str[0];

		UpperCase(str);
		PrintArray(str);
		
	}

	return 0;
}