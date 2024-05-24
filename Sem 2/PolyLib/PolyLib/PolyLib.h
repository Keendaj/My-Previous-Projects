/**
* \file
* \brief Реализация нового типа данных poly_t: полинома
*/
#pragma once
#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/**
 * \param begin Указатель на первый член полинома
 * \param length Число членов полинома
 */
typedef struct {
	int* begin;
	int length;
} poly_t;

/**
* \brief Создание объекта типа poly_t с нулевыми коэфициентами
* \param size Число членов полинома
* \return Возвращает объект типа poly_t
*/
poly_t PolyCreate(int size);

/**
* \brief Очистка памяти у объекта типа poly_t
* \param poly Полином
*/
void PolyDestroy(poly_t poly);

/**
* \brief Создание объекта типа poly_t с различными коэфициентам
* \param size Число членов полтинома
* \param array Массив с коэфициентами
* \return Возвращает объект типа poly_t
*/
poly_t PolyFrom(int size, int* array);

/**
* \brief Создание объекта типа poly_t из строки
* \param string Строка
* \param length Длина строки
* \return Возвращает объект типа poly_t
*/
poly_t PolyParse( char *string, int length);

/**
* \brief Создание строки из объекта типа poly_t
* \param poly Полином
* \return Возвращает объект типа char*
*/
char *PolyFormat(poly_t poly);

/**
* \brief Создание объекта типа poly_t из считанного файла
* \param filepath Путь до файла
* \return Возвращает объект типа poly_t
*/
poly_t PolyRead( char* filepath);

/**
* \brief Запись в файл объекта типа poly_t
* \param filepath Число, над которым работает программа
* \param poly Полином
*/
void PolyWrite( char* filepath, poly_t poly);

/**
* \brief Сложение двух объектов типа poly_t
* \param poly1 Первое слагаемое
* \param poly2 Второе слагаемое
* \return Возвращает объект типа poly_t
*/
poly_t PolyAdd( poly_t poly1,  poly_t poly2);

/**
* \brief Вычитание двух объектов типа poly_t
* \param poly1 Уменьшаемое
* \param poly2 Вычитаемое
* \return Возвращает объект типа poly_t
*/
poly_t PolySub( poly_t poly1,  poly_t poly2);

/**
* \brief Перемножение двух объектов типа poly_t
* \param poly1 Первой множитель
* \param poly2 Второй множитель
* \return Возвращает объект типа poly_t
*/
poly_t PolyMul( poly_t poly1,  poly_t poly2);

/**
* \brief Умножение всех коэфициентов полинома на число
* \param poly Полином
* \param mult Множителб
* \return Возвращает объект типа poly_t
*/
poly_t PolyMulInt( poly_t  poly, int mult);

/**
* \brief Вычисление значения полинома в точке
* \param poly Полином
* \param point Точка, в которой идёт вычисление
* \return Возвращает double, значение точки
*/
double PolyEvaluate( poly_t  poly, double point);

/**
* \brief Получение определённого коэфициента полинома
* \param poly Полином
* \param number Номер коэфициента, счёт идёт справа налево с 0 согласно правилам алгебры
* \return Возвращает int, значение коэфициента
*/
int PolyElement( poly_t  poly, int number);