/**
* \file
* \brief ���������� ������ ���� ������ poly_t: ��������
*/
#pragma once
#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/**
 * \param begin ��������� �� ������ ���� ��������
 * \param length ����� ������ ��������
 */
typedef struct {
	int* begin;
	int length;
} poly_t;

/**
* \brief �������� ������� ���� poly_t � �������� �������������
* \param size ����� ������ ��������
* \return ���������� ������ ���� poly_t
*/
poly_t PolyCreate(int size);

/**
* \brief ������� ������ � ������� ���� poly_t
* \param poly �������
*/
void PolyDestroy(poly_t poly);

/**
* \brief �������� ������� ���� poly_t � ���������� ������������
* \param size ����� ������ ���������
* \param array ������ � �������������
* \return ���������� ������ ���� poly_t
*/
poly_t PolyFrom(int size, int* array);

/**
* \brief �������� ������� ���� poly_t �� ������
* \param string ������
* \param length ����� ������
* \return ���������� ������ ���� poly_t
*/
poly_t PolyParse( char *string, int length);

/**
* \brief �������� ������ �� ������� ���� poly_t
* \param poly �������
* \return ���������� ������ ���� char*
*/
char *PolyFormat(poly_t poly);

/**
* \brief �������� ������� ���� poly_t �� ���������� �����
* \param filepath ���� �� �����
* \return ���������� ������ ���� poly_t
*/
poly_t PolyRead( char* filepath);

/**
* \brief ������ � ���� ������� ���� poly_t
* \param filepath �����, ��� ������� �������� ���������
* \param poly �������
*/
void PolyWrite( char* filepath, poly_t poly);

/**
* \brief �������� ���� �������� ���� poly_t
* \param poly1 ������ ���������
* \param poly2 ������ ���������
* \return ���������� ������ ���� poly_t
*/
poly_t PolyAdd( poly_t poly1,  poly_t poly2);

/**
* \brief ��������� ���� �������� ���� poly_t
* \param poly1 �����������
* \param poly2 ����������
* \return ���������� ������ ���� poly_t
*/
poly_t PolySub( poly_t poly1,  poly_t poly2);

/**
* \brief ������������ ���� �������� ���� poly_t
* \param poly1 ������ ���������
* \param poly2 ������ ���������
* \return ���������� ������ ���� poly_t
*/
poly_t PolyMul( poly_t poly1,  poly_t poly2);

/**
* \brief ��������� ���� ������������ �������� �� �����
* \param poly �������
* \param mult ���������
* \return ���������� ������ ���� poly_t
*/
poly_t PolyMulInt( poly_t  poly, int mult);

/**
* \brief ���������� �������� �������� � �����
* \param poly �������
* \param point �����, � ������� ��� ����������
* \return ���������� double, �������� �����
*/
double PolyEvaluate( poly_t  poly, double point);

/**
* \brief ��������� ������������ ����������� ��������
* \param poly �������
* \param number ����� �����������, ���� ��� ������ ������ � 0 �������� �������� �������
* \return ���������� int, �������� �����������
*/
int PolyElement( poly_t  poly, int number);