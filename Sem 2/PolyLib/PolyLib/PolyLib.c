#include "PolyLib.h"
#define max(a, b) ((a) >= (b)) ? (a) : (b)

poly_t PolyCreate(int size) {
	poly_t result;
	result.length = size;
	result.begin = malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++) {
		result.begin[i] = 0;
	}
	return result;
}

void PolyDestroy(poly_t poly) {
	free(poly.begin);
	poly.length = 0;
}

poly_t PolyFrom(int size, int* array) {
	poly_t result = PolyCreate(size);
	for(int i = 0; i < size; i++){
		result.begin[i] = array[i];
	}
	return result;
}
poly_t PolyParse(char* string, int length) {
	int i = 0;
	int max_degree = -1;
	char is_counting = 0;
	int temp = 0;
	while (1) {
		if (string[i] == 'x') {
			is_counting = 1;
			i += 2;
			continue;
		}
		if (is_counting) {
			if (string[i] == ' ') {
				max_degree = temp;
				break;
			}
			temp = temp * 10 + string[i]-'0';
		}
		i++;
	}
	poly_t poly = PolyCreate(max_degree+1);
	int current_degree;
	temp = 0;
	i = 0;
	int times = 1;
	if (string[0] == '-') {
		times = -1;
	}
	int skip;
	while (string[i]!=0) {
		if (string[i] == 'x') {
			current_degree = 0;
			i+=1;
			if (string[i] != '^') {
				current_degree = 1;
					
			}
			else {
				i+=1;
				while (string[i] != ' ') {
					current_degree = current_degree * 10 + string[i] - '0';
					i++;
				}
			}
			i++;
			
			poly.begin[max_degree - current_degree] = temp*times;
			temp = 0;
			if (string[i] == '-') {
				times = -1;
			}
			else if (string[i] == '+') {
				times = 1;
			}
			i += 2;
			continue;
		}
		temp = temp * 10 + string[i] - '0';
		i++;
	}
	if(temp!=0){
		poly.begin[max_degree] = temp * times;
	}
	

	return poly;
}

void CheckSize(char* string, int string_pointer, int *string_size) {
	if (string_pointer >= string_size-1) {
		*string_size *= 2;
		string = realloc(string, sizeof(int) * (*string_size));
	}
}

char* PolyFormat(poly_t poly) {
	char* string = malloc(sizeof(int) * 10);
	int string_pointer = 0;
	int string_size = 10;
	int temp = 0;
	int skip;
	for (int i = 0; i < poly.length; i++) {
		if (poly.begin[i] == 0) {
			continue;
		}
		if (poly.begin[i] < 0) {
			CheckSize(string, string_pointer + 2, &string_size);
			string[string_pointer] = '-';
			string_pointer++;
			string[string_pointer] = ' ';
			string_pointer++;
			
		}
		else if(i!=0){
			CheckSize(string, string_pointer + 2, &string_size);
			string[string_pointer] = '+';
			string_pointer++;
			string[string_pointer] = ' ';
			string_pointer++;
			
		}
		
		temp = poly.begin[i];
		skip = 0;
		while (temp) {
			temp /= 10;
			skip++;
		}
		CheckSize(string, string_pointer + skip, &string_size);
		temp = abs(poly.begin[i]);
		for (int j = 0; j < skip; j++) {
			string[string_pointer + skip - j - 1] = temp % 10 + '0';
			temp /= 10;
		}
		string_pointer += skip;
		CheckSize(string, string_pointer + 2, &string_size);
		if (poly.length - i - 1 > 0) {
			string[string_pointer] = 'x';
			string_pointer++;
		}
	
		if (poly.length - i - 1 > 1) {
			string[string_pointer] = '^';
			string_pointer++;
			temp = poly.length - i - 1;
			skip = 0;
			while (temp) {
				temp /= 10;
				skip++;
			}
			CheckSize(string, string_pointer + skip + 1, &string_size);
			temp = poly.length - i - 1;
			for (int j = 0; j < skip; j++) {
				string[string_pointer + skip - j - 1] = temp % 10 + '0';
				temp /= 10;
			}
			string_pointer += skip;
		}
		
		if (i < poly.length - 1) {
			string[string_pointer] = ' ';
			string_pointer++;
		}
	}
	string[string_pointer] = 0;
	return string;
}
poly_t PolyRead(char* filepath) {
	FILE* my_file = fopen(filepath, "r");
	int times = 1;
	char c = 1;
	int temp = 0;
	int temp2 = 0;
	int max_degree = -1;
	c = fgetc(my_file);
	poly_t poly = PolyCreate(1);
	if (c == '-') {
		c = fgetc(my_file);
		temp = 0;
		c = fgetc(my_file);
		while (c != 'x' && c != EOF) {
			temp = temp * 10 + c - '0';
			c = fgetc(my_file);
		}
		c = fgetc(my_file);
		if (c == '^') {
			c = fgetc(my_file);
		}
		temp2 = 0;
		c = fgetc(my_file);
		while (c != EOF && c != ' ') {
			temp2 = temp2 * 10 + c - '0';
			c = fgetc(my_file);
		}
		if (max_degree == -1) {
			max_degree = temp2;
			poly = PolyCreate(max_degree + 1);
		}
		poly.begin[0] = temp * -1;

	}
	else {
		temp = 0;
		while (c != 'x' && c != EOF) {
			temp = temp * 10 + c - '0';
			c = fgetc(my_file);
		}
		c = fgetc(my_file);
		if (c == '^') {
			c = fgetc(my_file);
		}
		temp2 = 0;
		while (c != EOF && c != ' ') {
			temp2 = temp2 * 10 + c - '0';
			c = fgetc(my_file);
		}
		if (max_degree == -1) {
			max_degree = temp2;
			poly = PolyCreate(max_degree + 1);
		}
		poly.begin[0] = temp;
	}
	c = fgetc(my_file);
	while (c != EOF && c != 0) {
		if (c == '-') {
			c = fgetc(my_file);
			temp = 0;
			c = fgetc(my_file);
			while (c != 'x' && c!= EOF) {
				temp = temp * 10 + c - '0';
				c = fgetc(my_file);
			}
			c = fgetc(my_file);
			if (c != '^') {
				if (c == EOF) {
					poly.begin[max_degree] = temp;
					continue;
				}
				poly.begin[max_degree - 1] = temp * -1;
				c = fgetc(my_file);
				continue;
			}
			temp2 = 0;
			c = fgetc(my_file);
			while (c != EOF && c != ' ') {
				temp2 = temp2 * 10 + c - '0';
				c = fgetc(my_file);
			}
			poly.begin[max_degree - temp2] = temp * -1;

		}
		else if(c=='+'){
			c = fgetc(my_file);
			temp = 0;
			c = fgetc(my_file);
			while (c != 'x' && c != EOF) {
				temp = temp * 10 + c - '0';
				c = fgetc(my_file);
			}
			c = fgetc(my_file);
			if (c != '^') {
				if (c == EOF) {
					poly.begin[max_degree] = temp;
					continue;
				}
				poly.begin[max_degree - 1] = temp * -1;
				c = fgetc(my_file);
				continue;
			}
			temp2 = 0;
			c = fgetc(my_file);
			while (c != EOF && c != ' ') {
				temp2 = temp2 * 10 + c - '0';
				c = fgetc(my_file);
			}
			poly.begin[max_degree - temp2] = temp;
		}
	}
	fclose(my_file);
	return poly;
}
void PolyWrite(const char* filepath, poly_t poly) {
	FILE* my_file = fopen(filepath, "w");
	int temp = 0;
	int skip;
	for (int i = 0; i < poly.length; i++) {
		if (poly.begin[i] == 0) {
			continue;
		}
		if (poly.begin[i] < 0) {
			fputc('-',my_file);
			fputc(' ', my_file);
		}
		else if(i != 0){
			fputc('+', my_file);
			fputc(' ', my_file);
		}
		temp = poly.begin[i];
		skip = 0;
		while (temp) {
			temp /= 10;
			skip++;
		}
		temp = abs(poly.begin[i]);
		char* temp_str = malloc(sizeof(char) * skip);
		for (int j = 0; j < skip; j++) {
			temp_str[j] = temp % 10 + '0';
			temp /= 10;
		}
		for (int j = skip-1; j >= 0; j--) {
			fputc(temp_str[j], my_file);
		}
		if (poly.length - i - 1 > 0) {
			fputc('x', my_file);
		}

		if (poly.length - i - 1 > 1) {
			fputc('^', my_file);
			temp = poly.length - i - 1;
			skip = 0;
			while (temp) {
				temp /= 10;
				skip++;
			}
			char* temp_str = malloc(sizeof(char) * skip);
			temp = poly.length - i - 1;
			for (int j = 0; j < skip; j++) {
				temp_str[j] = temp % 10 + '0';
				temp /= 10;
			}
			for (int j = skip - 1; j >= 0; j--) {
				fputc(temp_str[j], my_file);
			}
		}

		if (i < poly.length - 1) {
			fputc(' ', my_file);
		}
	}

	fclose(my_file);
}
poly_t PolyAdd(poly_t poly1, poly_t poly2) {
	poly_t result_poly = PolyCreate(max(poly1.length, poly2.length));
	int p1 = poly1.length-1, p2 = poly2.length-1;
	for (int i = result_poly.length - 1; i >= 0; i--) {
		if (p1 >= 0) {
			result_poly.begin[i] += poly1.begin[p1];
			p1--;
		}
		if (p2 >= 0) {
			result_poly.begin[i] += poly2.begin[p2];
			p2--;
		}
	}
	return result_poly;
}
poly_t PolySub( poly_t poly1,  poly_t poly2) {
	poly_t result_poly = PolyCreate(max(poly1.length, poly2.length));
	int p1 = poly1.length - 1, p2 = poly2.length - 1;
	for (int i = result_poly.length - 1; i >= 0; i--) {
		if (p1 >= 0) {
			result_poly.begin[i] += poly1.begin[p1];
			p1--;
		}
		if (p2 >= 0) {
			result_poly.begin[i] -= poly2.begin[p2];
			p2--;
		}
	}
	return result_poly;
}
poly_t PolyMul(poly_t poly1, poly_t poly2) {
	poly_t result_poly = PolyCreate(poly1.length + poly2.length - 1);
	for (int i = 0; i < poly1.length; i++) {
		for (int j = 0; j < poly2.length; j++) {
			result_poly.begin[j + i] += poly1.begin[i] * poly2.begin[j];
		}
	}
	return result_poly;
}
poly_t PolyMulInt(poly_t poly, int mult) {
	poly_t result_poly = PolyCreate(poly.length);
	for (int i = poly.length - 1; i >= 0; i--) {
		result_poly.begin[i] =  poly.begin[i] * mult;
	}
	return result_poly;
}
double PolyEvaluate( poly_t poly, double point) {
	double result = 0;
	double temp = 1;
	for (int i = poly.length - 1; i >= 0; i--) {
		result += temp * poly.begin[i];
		temp *= point;
	}
	return result;
}
int PolyElement(poly_t poly, int number) {
	return poly.begin[poly.length - number - 1];
}
