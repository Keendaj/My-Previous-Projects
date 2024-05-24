#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 20
#define ACCURACY 1e-6
#pragma warning(disable:4996)

char __CalcLength(int a) {
	char length = 0;
	do {
		a /= 10;
		length++;
	} while (a != 0);
	return length;
}

int __Pow(int a, int b) {
	int res = 1;
	for (int i = 0; i < b; i++) {
		res *= a;
	}
	return res;
}

typedef struct {
	int IntPart;
	int FloatPart;
	char IntLength;
	char FloatLength;
}fixed_t;

const fixed_t ZERO = { 0,0,1,0 };

fixed_t FixFromInt(int i) {
	char ilength;
	
	ilength = __CalcLength(i);
	fixed_t c = {i, 0, ilength, 1};

	return c;
}

fixed_t FixFromDouble(double a) {
	int IsNegative = 1;
	if (a < 0) {
		IsNegative = -1;
		a *= -1;
	}
	int i = a, f = 0;
	char ilength, flength = 0;
	a = a - i;
	ilength = __CalcLength(i);
	while ((1 - a  > ACCURACY) && a>ACCURACY) {
		a *= 10;
		f = f*10 + a;
		a -= f % 10;
		flength++;
	}
	int x = a * 10;
	if (x >= 5) {
		f++;
	}
	fixed_t c = {IsNegative*i, IsNegative*f, ilength, flength};
	return c;
}

int FixAsInt(fixed_t c) {
	return c.IntPart;
}

double FixAsDouble(fixed_t c) {//Нужно добавить учёт отрицательного
	double res = c.IntPart;
	double x = 0;
	char mylength = 0;
	int counter = 10;
	while (mylength <= c.FloatLength) {
		x /= 10;
		x += (c.FloatPart % counter)/(counter/10);
		counter *= 10;
		mylength++;
	}
	return res+x;
}

fixed_t FixParse(char* x) {
	int ptr = 4, IsNegative = 1;
	int i = 0, f = 0;
	char ilength = 0, flength = 0;
	if (x[ptr] == '-') {
		IsNegative = -1;
		ptr++;
	}
	while (x[ptr]!='.' && x[ptr] != ',')
	{
		i *= 10;
		i += x[ptr] - 48;
		ilength++;
		ptr++;
	}
	ptr++;
	while (x[ptr] != ']')
	{
		f *= 10;
		f += x[ptr] - 48;
		flength++;
		ptr++;
	}


	fixed_t c = { IsNegative*i, IsNegative*f, ilength, flength };
	return c;
}

char* FixFormat(fixed_t c) {
	char* s = malloc(sizeof(char)*(6+c.FloatLength + c.IntLength));
	int IsNegative = 1, pptr = 0, counter = 10, newptr;
	s[pptr] = 'F';
	pptr++;
	s[pptr] = 'I';
	pptr++;
	s[pptr] = 'X';
	pptr++;
	s[pptr] = '[';
	pptr++;
	if (c.IntPart < 0) {
		IsNegative = -1;
		s = realloc(s, sizeof(char) * (7+c.FloatLength + c.IntLength));
		s[pptr] = '-';
		pptr++;
	}
	newptr = pptr;
	for (int i = c.IntLength; i > 0; i--) {
		s[pptr+i-1] = (IsNegative*c.IntPart % counter)/(counter/10)+48;
		counter *= 10;
		newptr++;
	}
	pptr = newptr;
	s[pptr] = '.';
	pptr++;
	counter = 10;
	newptr = pptr;
	for (int i = c.FloatLength; i > 0; i--) {
		s[pptr + i-1] = (IsNegative * c.FloatPart % counter) / (counter / 10)+48;	
		counter *= 10;
		newptr++;
	}
	s[newptr] = ']';

	return s;
}

fixed_t FixRead(char const *filepath) {
	FILE* myfile = fopen(filepath, "r");
	if (myfile == NULL) {
		fixed_t c = { 0,0,-1,-1 };
		return c;
	}
	int IsNegative = 1;
	int i=0, f=0, ilength=0, flength=0, IsI = 0, IsF = 0;
	char s;
	while (1)
	{
		s = fgetc(myfile);
		if (s == EOF) {
			break;
		}
		if (s == '[') {
			IsI = 1;
		}
		else if (s == ']') {
			break;
		}
		else if (s == '.') {
			IsI = 0;
			IsF = 1;
		}
		else if (s == '-') {
			IsNegative = -1;
		}
		else if (IsI) {
			i *= 10;
			i += s - 48;
			ilength++;
		}
		else if (IsF) {
			f *= 10;
			f += s - 48;
			flength++;
		}
		
	}

	fclose(myfile);

	fixed_t c = {IsNegative*i, IsNegative*f, ilength, flength};
	return c;
}

char FixWrite(fixed_t c, char const* filename) {
	FILE* myfile = fopen(filename,"w");
	if (myfile == NULL) {
		return 0;
	}
	char IsNegative = 1;
	fputs("FIX[",myfile);
	if (c.IntPart < 0) {
		IsNegative = -1;
		fputc('-', myfile);
	}
	int counter = __Pow(10, c.IntLength);
	for (int i = 0; i < c.IntLength; i++) {
		fprintf(myfile, "%d", IsNegative * (c.IntPart % counter) / (counter/10));
		counter /= 10;
	}
	fputc('.',myfile);
	counter = __Pow(10, c.FloatLength);
	for (int i = 0; i < c.FloatLength; i++) {
		fprintf(myfile, "%d", IsNegative * (c.FloatPart % counter) / (counter / 10));
		counter /= 10;
	}
	fputc(']', myfile);
	fclose(myfile);
	return 1;
}

fixed_t FixAdd(fixed_t a, fixed_t b) {
	char IntLength = a.IntLength, FloatLength = a.FloatLength;
	if (a.IntLength < b.IntLength) {
		IntLength = b.IntLength;
	}
	if (a.FloatLength < b.FloatLength) {
		FloatLength = b.FloatLength;
	}
	int icounter = __Pow(10, IntLength);
	int fcounter = __Pow(10, FloatLength);
	int i = a.IntPart + b.IntPart;
	int f = a.FloatPart*(__Pow(10, FloatLength-a.FloatLength)) + b.FloatPart*(__Pow(10, FloatLength - b.FloatLength));

	if (i / icounter != 0) {
		IntLength++;
	}
	while (f < 0 && i > 0) {
		i--;
		f += fcounter;
	}
	while (f>=fcounter && i > 0) {
		f -= fcounter;
		i++;
	}
	while (f > 0 && i < 0) {
		i++;
		f -= fcounter;
	}
	while (f <= -1*fcounter && i < 0) {
		f += fcounter;
		i--;
	}
	while (f % 10 == 0) {}
	{
		f /= 10;
		FloatLength -= 1;
	}

	fixed_t c = { i, f, IntLength, FloatLength };
	return c;
}
fixed_t FixSub(fixed_t a, fixed_t b) {
	fixed_t x = b;
	x.FloatPart *= -1;
	x.IntPart *= -1;
	fixed_t c = FixAdd(a, x);

	return c;
}

fixed_t FixMul(fixed_t a, fixed_t b) {
	if ((b.FloatLength==0 && b.IntPart == 0)||(a.FloatLength == 0 && a.IntPart==0)) {
		fixed_t c = {0,0,1,0};
		return c;
	}
	int TotalFloatLength = a.FloatLength + b.FloatLength;
	long counter = __Pow(10, TotalFloatLength);
	long result;
	long currb = b.IntPart * __Pow(10, b.FloatLength) + b.FloatPart;
	long curra = a.IntPart * __Pow(10, a.FloatLength) + a.FloatPart;
	result = curra * currb;
	int f = result % counter;
	int i = result / counter;
	int cintlength = __CalcLength(i);
	while (f%10==0)
	{
		f /= 10;
		TotalFloatLength -= 1;
	}

	fixed_t c = { i,f,cintlength ,TotalFloatLength};
	return c;
}
fixed_t FixDiv(fixed_t a, fixed_t b) {
	char FloatLength = a.FloatLength;
	if (a.FloatLength < b.FloatLength) {
		FloatLength = b.FloatLength;
	}
	long long x1 = a.IntPart * __Pow(10, FloatLength) + a.FloatPart* __Pow(10,FloatLength-a.FloatLength);
	long long x2 = b.IntPart * __Pow(10, FloatLength) + b.FloatPart * __Pow(10, FloatLength - b.FloatLength);
	long long i = 0;
	long long f = 0;
	char ilength = 0, flength = 0;
	char currPart = 1, prevaction = 2;
	while (x1 != 0) {
		if (x1 / x2 == 0) {
			currPart = 0;
			if (prevaction == 1) {
				flength++;
			}
			prevaction = 1;
			x1 *= 10;
			continue;
		}
		if (currPart) {
			i *= 10;
			i += x1 / x2;
			x1 %= x2;
			ilength++;
			prevaction = 2;
		}
		else {
			if (f * 10 > INT_MAX) {
				break;
			}
			f *= 10;
			f += x1 / x2;
			x1 %= x2;
			flength++;
			prevaction = 3;
		}
		
	}
	fixed_t c = { i,f,ilength,flength };
	return c;
}

fixed_t FixNegate(fixed_t c) {
	fixed_t res = { -1 * c.IntPart,-1 * c.FloatPart,c.IntLength,c.FloatLength };
	return res;
}

fixed_t FixReciprocal(fixed_t c) {
	fixed_t a = { 1,0,1,0 };
	return FixDiv(a, c);
}

fixed_t FixAbs(fixed_t c) {
	int IsNegative = 1;
	if (c.IntPart < 0) {
		IsNegative = 1;
	}
	fixed_t b = { c.IntPart * IsNegative,c.FloatPart * IsNegative,c.IntLength,c.FloatLength };
	return b;
}

fixed_t FixRound(fixed_t c) {
	char Dif = 0;
	if (abs(c.FloatPart) < 5 * __Pow(10, c.FloatLength - 1)) {
		Dif = -1;
	}
	fixed_t b = { c.IntPart + Dif,0,c.IntLength,0 };
	return b;
}

fixed_t FixFloor(fixed_t c) {
	if ((c.IntPart >= 0 && c.FloatPart>=0) || c.FloatPart == 0) {
		return c;	}
	fixed_t b = { c.IntPart -1,0,c.IntLength,0 };
	return b;
}

fixed_t FixCeil(fixed_t c) {
	if ((c.IntPart <= 0 && c.FloatPart <= 0) || c.FloatPart == 0) {
		return c;
	}
	fixed_t b = { c.IntPart + 1,0,c.IntLength,0 };
	return b;
}

char FixCompare(fixed_t a, fixed_t b) {
	if (a.IntPart > b.IntPart) {
		return 1;
	}
	else if (b.IntPart > a.IntPart) {
		return -1;
	}
	else {
		char FloatLength = a.FloatLength;
		if (a.FloatLength < b.FloatLength) {
			FloatLength = b.FloatLength;
		}
		int AFloat = __Pow(10, FloatLength - a.FloatLength) * a.FloatPart;
		int BFloat = __Pow(10, FloatLength - b.FloatLength) * b.FloatPart;
		if (AFloat > BFloat) {
			return 1;
		}
		else if (BFloat > AFloat) {
			return -1;
		}
		return 0;
	}
}