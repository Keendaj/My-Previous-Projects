#include<stdio.h>
#include<math.h>
#include<locale.h>
#include<ctype.h>
#pragma warning(disable:4996)


int main() {
	setlocale(LC_CTYPE, "Russian");
	int f = 0, cc, mg = 9;//CC - система счисления, mg - магическое число
	long long x, y=0, z, k=0;//Числа x,y,z - участвуют в пересчёте, k - количество пересчитанных чисел
	unsigned char m[100];//m - массив с цифрами/буквами, n - массив, в котором обозначено является данный символ буквой или цифрой
	char g, t = 'd';

	printf("Введите систему счисления: \n");
	scanf("%d", &cc);
	printf("Введите магическое число: \n");
	scanf(" %c", &t);
	mg = t;
	if (mg >= 'a' && mg <= 'z') {
		mg = mg - 87;
	}
	else if (mg >= 'A' && mg <= 'Z') {
		mg = mg - 10;
	}
	else {
		mg = mg - 48;
	}

	m[0] = mg + '0';
	z = mg;
	for (int i = 1; i < 100; i++) {
		//Подсчёт числа с опрой на предыдущее число
		x = z * mg;
		x = x + y;
		y = 0;

		//Проверка на количество разрядов, если больше сс, то запоминание второго разряда
		y = x / cc;
		z = x % cc;
		z = z - '0'+'0';
		//Проверка на возможность записи цифрой и преобразование
		if (z >= 10) {
			g = 'a' + z - 10;
		}
		else {
			g = z + '0';
		}

		m[i] = g;
		

		//Проверка на возможность остановки
		if (z == mg && y == 0) {
			break;
		}
		k++;

	}


	//Вывод символа в зависимости от его типа
	for (int i = k; i >= 0; i--) {
		printf("%c", m[i]);
	}

	return 0;
}