#include <stdio.h>
#include <math.h>
#pragma warning(disable:4996)
#include <locale.h>


double g(double x) {

	return pow(sin(x), 2);
}
double f(double x, double res) {
	double u = 1, s = 0, currentK = 1, currentx = 1, prevs = -1;
	int i = 0;
	currentK /= 4;
	currentK *= 2;
	currentK *= -1;
	


	while(s + u != prevs) {
		i++;
		currentK *= 4;
		currentK /= 2 * i;
		currentK /= 2 * i - 1;
		currentK *= -1;
		currentx *= x * x;
		u = currentK * currentx;
		prevs = s;
		s += u;
	}
	return prevs;

}
void PrintTable(double a, double b, double m) {
	double delta1 = (b-a) / (m-1), x, delta2, f1, g1;
	int i = 0;
	printf("+-----+-----+----------+----------+---------------+\n");
	printf("|  i  |  x  |    f     |    g     |  f(x) - g(x)  |\n");
	printf("+-----+-----+----------+----------+---------------+\n");
	for (x = a; x <= b; x += delta1) {
		g1 = g(x);
		f1 = f(x, g1);
		delta2 = f1 - g1;
		if (delta2 >= 0) {
			printf("|  %d  | %1.1f | %1.2le | %1.2le |    %1.2le   |\n", i, x, f1, g1, delta2);
		}
		else {
			printf("|  %d  | %1.1f | %1.2le | %1.2le |   %1.2le   |\n", i, x, f1, g1, delta2);
		}
		
		i++;
		printf("+-----+-----+----------+----------+---------------+\n");
	}
	if( x > b) {
		x = b;
		g1 = g(x);
		f1 = f(x, g1);
		delta2 = f1 - g1;
		if (delta2 >= 0) {
			printf("|  %d  | %1.1f | %1.2le | %1.2le |    %1.2le   |\n", i, x, f1, g1, delta2);
		}
		else {
			printf("|  %d  | %1.1f | %1.2le | %1.2le |   %1.2le   |\n", i, x, f1, g1, delta2);
		}
		printf("+-----+-----+----------+----------+---------------+\n");
	}
}
int main() {
	setlocale(LC_CTYPE, "Russian");

	double a, b, m;
	printf("¬ведите левую границу:\n");
	scanf("%lf", &a);
	printf("¬ведите правую границу:\n");
	scanf("%lf", &b);
	printf("¬ведите число иксов:\n");
	scanf("%lf", &m);
	while (!(a>=-1 && a<=1)) {
		scanf("%lf", &a);
	}
	while (!(b >= -1 && b <= 1)) {
		scanf("%lf", &b);
	}
	while (m<=1) {
		scanf("%lf", &m);
	}
	PrintTable(a, b, m);
	return 0;
}