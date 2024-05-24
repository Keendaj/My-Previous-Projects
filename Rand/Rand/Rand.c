#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>

#define HIST_CHAR_BAR 'o'
#define HIST_CHAR_SPACE 183

//////////////////////////////////////////////////////////////////////////////
/**
* Возвращает вещественное случайное число, равномерно распределённое
* на полуоткрытом интервале [a, b).
*
* @param a нижняя граница
* @param b верхняя граница
*
* @return Случайное число от a до b (не включая верхнюю границу).
*/
double Random(double a, double b) {
	double s = rand();
	s /= RAND_MAX+1;
	s *= b - a;
	s += a;
	return s;
}

/**
* Заполняет массив равномерно распределёнными случайными числами.
*
* @param arr массив
* @param size количество элементов в массиве
* @param a нижняя граница
* @param b верхняя граница (не включается в интервал)
*
* @see Random()
*/
void FillRandom(double arr[], int size, double a, double b) {
	// TODO: 1. Заполните массивы.
	for (int i = 0; i < size; i++) {
		arr[i] = Random(a, b);
	}
}

/**
* Печатает элементы массива через запятую в фигурных скобках.
*
* @param arr массив
* @param size количество элементов в массиве
*/
void Print(double const arr[], int size) {
	// TODO: 1. Заполните массивы.
	for (int i = 0; i < size; i++) {
		printf("%lf\n", arr[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////
/**
* Строит гистограмму значений элементов массива.
*
* Заполняет массив counters[] на основании значений элементов массива arr[],
* подсчитывая, сколько их попало в соответствующий подынтервал
* полного интервала [a, b). Элементы массива, не попадающие в указанный
* интервал от a до b игнорируются.
*
* @param arr массив
* @param size количество элементов в массиве
* @param a нижняя граница
* @param b верхняя граница (не включается в интервал)
* @param counters заполняемый массив
* @param numCounters количество подынтервалов подсчёта
*/
void BuildHistogram(double const arr[], int size,
	// TODO: 2. Вычислите данные для гистограммы.
	double left, double right, int counters[], int numCounters) {
	double currD;
	int currI;
	for (int i = 0; i < numCounters; i++) {
		counters[i]=0;

	}
	for (int i = 0; i < size; i++) {
		currD = arr[i];
		currD -=left;
		currD /= (right - left);
		currD *= numCounters;
		currI = currD;
		counters[currI]++;
		
	}

}

/**
* Печатает элементы массива через запятую в фигурных скобках.
*
* @param counters массив
* @param numCounters количество элементов в массиве
*/
void PrintHistogram(int counters[], int numCounters) {
	// TODO: 2. Вычислите данные для гистограммы.
	for (int i = 0; i < numCounters; i++) {
		printf("%d\n", counters[i]);
	}
}

/**
* Печатает горизонтальную гистограмму значений элементов массива.
*
* @param counters массив интервалов, содержащий количество элементов,
* попавших в соответствующий подынтервал
* @param numCounters количество подынтервалов подсчёта
* @param width полная ширина поля вывода гистограммы, в знакоместах
*/
void DrawHistogramH(int counters[], int numCounters, int width) {
	// TODO: 3. Нарисуйте диаграмму.
	int d;
	double k, maxN = 0;
	for (int i = 0; i < numCounters;i++) {
		if (maxN < counters[i]){
			maxN = counters[i];
		}
	}
	k = width / maxN;
	for (int i = 0; i < numCounters; i++) {
		d = 0;
		printf("%d ", i);
		for (int j = 0; j <= k * counters[i]-1; j++) {
			printf("%c", HIST_CHAR_BAR);
			d++;
		}
		for (int y = 0; y < (width - d); y++) {
			printf("%c", HIST_CHAR_SPACE);
		}
		printf("\n");
	}
	


}
void DrawHistogramV(int counters[], int numCounters, int width) {
	double k, maxN = 0;
	for (int i = 0; i < numCounters; i++) {
		if (maxN < counters[i]) {
			maxN = counters[i];
		}
	}
	k = width / maxN;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < numCounters; j++) {
			if (k * counters[j] + 1 <= width - i) {
				printf("%c ", HIST_CHAR_SPACE);
				continue;
			}
			printf("%c ", HIST_CHAR_BAR);
		}
		printf("\n");

	}
	for (int i = 0; i < numCounters; i++) {
		printf("%d ", i);
	}
	printf("\n");


}

//////////////////////////////////////////////////////////////////////////////
int main(void) {
	const int PRINT_MAX = 20;
	const double RANDOM_MIN = 0.2;
	const double RANDOM_MAX = 0.6;
	const double HIST_MIN = 0.2;
	const double HIST_MAX = 0.6;
	const int HIST_LINES = 10;
	const int HIST_LENGTH = 20;
	int size = 10;
	char d_type = 0;
	double* numbers = NULL;
	int* hist = NULL;
	setlocale(LC_CTYPE, "Russian");
	// TODO: 0. Взляните на случайные числа. Напечатайте несколько в цикле.
	// При желании можно рандомизировать ГПСЧ текущим числом секунд
	// srand((unsigned)time(0));
	// ...
	// Подготовьтесь к эксперименту
	printf("\nВведите количество чисел: ");
	scanf("%i", &size);
	while (d_type != 'H' && d_type != 'V') {
		printf("\nВведите тип гистограммы из возможных - H/V: ");
		scanf(" %c", &d_type);
	}
	// Выделите память
	numbers = malloc(size * sizeof(double));
	hist = malloc(HIST_LINES * sizeof(int));
	// Заполните массивы
	printf("\nРавномерная СВ (первые %i чисел):\n", PRINT_MAX);
	FillRandom(numbers, size, RANDOM_MIN, RANDOM_MAX);
	Print(numbers, size < PRINT_MAX ? size : PRINT_MAX);
	// Постройте гистограмму равномерной случайной величины
	BuildHistogram(numbers, size, HIST_MIN, HIST_MAX, hist, HIST_LINES);
	PrintHistogram(hist, HIST_LINES);
	if (d_type == 'H') {
		DrawHistogramH(hist, HIST_LINES, HIST_LENGTH);
		
	}
	else {
		DrawHistogramV(hist, HIST_LINES, HIST_LENGTH);
	}
	
	
	// Освободите память
	free(hist);
	free(numbers);
	return 0;
}