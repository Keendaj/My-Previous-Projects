#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#include <locale.h>
#include <math.h>
#define PI 3.14159265358979323846
typedef enum {
	CIRCLE,
	RECTANGLE,
	POLYGON
} ShapeType;

typedef enum {
	RED,
	GREEN,
	BLUE
} Color;
typedef struct {
	ShapeType type;
	Color color;
	union {
		struct {
			float radius;
		} circle;
		struct {
			float width;
			float height;
		} rectangle;
		struct {
			int sides;
			float side_length;
		} polygon;
	} shape_details;
} Shape;

Shape* ReadBinary(char const* filename, int* length) {
	fseek(filename, 0, SEEK_END);
	int size = ftell(filename);
	*length = size/ sizeof(Shape);
	fseek(filename, 0, SEEK_SET);
	Shape* arr = malloc(size);
	fread(arr, sizeof(Shape), *length, filename);
	return arr;
}


int main() {
	setlocale(LC_CTYPE, "Russian");
	printf("Вариант 11\n");
	int length, *Figures = calloc(3, sizeof(int)), *Colors = calloc(3,sizeof(int));
	float Areas = 0;
	Shape* arr;
	FILE* myfile = fopen("Text.bin", "rb");
	arr = ReadBinary(myfile, &length);
	for (int i = 0; i < length; i++) {
		Figures[arr[i].type]++;
		Colors[arr[i].color]++;
		switch (arr[i].type)
		{
			case 0:
				Areas += PI * arr[i].shape_details.circle.radius * arr[i].shape_details.circle.radius;
				break;
			case 1:
				Areas += arr[i].shape_details.rectangle.height * arr[i].shape_details.rectangle.width;
				break;
			case 2:
				Areas += arr[i].shape_details.polygon.sides * arr[i].shape_details.polygon.side_length * arr[i].shape_details.polygon.side_length / (4 * tan(PI / arr[i].shape_details.polygon.sides));
				break;
		}
	}
	printf("Количество фигур\n\tКругов: %d\n\tКвадратов: %d \n\tМногоугольников: %d\n", Figures[0], Figures[1], Figures[2]);
	printf("Количество цветов\n\tКрасных: %d\n\tЗелёных: %d\n\tСиних: %d\n",Colors[0], Colors[1], Colors[2]);
	printf("Суммарная площадь всех фигур: %.2f", Areas);
	fclose(myfile);

	return 0;
}
