#include<stdio.h>
#include<math.h>
#include<locale.h>
#include<ctype.h>
#pragma warning(disable:4996)


int main() {
	setlocale(LC_CTYPE, "Russian");
	int f = 0, cc, mg = 9;//CC - ������� ���������, mg - ���������� �����
	long long x, y=0, z, k=0;//����� x,y,z - ��������� � ���������, k - ���������� ������������� �����
	unsigned char m[100];//m - ������ � �������/�������, n - ������, � ������� ���������� �������� ������ ������ ������ ��� ������
	char g, t = 'd';

	printf("������� ������� ���������: \n");
	scanf("%d", &cc);
	printf("������� ���������� �����: \n");
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
		//������� ����� � ����� �� ���������� �����
		x = z * mg;
		x = x + y;
		y = 0;

		//�������� �� ���������� ��������, ���� ������ ��, �� ����������� ������� �������
		y = x / cc;
		z = x % cc;
		z = z - '0'+'0';
		//�������� �� ����������� ������ ������ � ��������������
		if (z >= 10) {
			g = 'a' + z - 10;
		}
		else {
			g = z + '0';
		}

		m[i] = g;
		

		//�������� �� ����������� ���������
		if (z == mg && y == 0) {
			break;
		}
		k++;

	}


	//����� ������� � ����������� �� ��� ����
	for (int i = k; i >= 0; i--) {
		printf("%c", m[i]);
	}

	return 0;
}