#include <stdio.h>
#define SIZE1 sizeof(int)*8
#define SIZE2 (sizeof(int)*8)


int main() {
	char size = sizeof(int) * 8;
	int x = 64;
	printf("%d\n", x/SIZE1);
	printf("%d\n", x / SIZE2);
	printf("%d\n", x / size);



	return 1;
}