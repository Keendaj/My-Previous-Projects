/**
* \file
 * \brief Реализация нового типа данных fixed_t: число с фиксированной точкой
 */
#ifndef FIXLIB_H
#define FIXLIB_H

 /**
 * \param IntPart Целочисленная часть числа
 * \param FloatPart Вещественная часть числа
 * \param IntLength Длина целочисленной части
 * \param FloatLength Длина вещественной части
 */
typedef struct {
	int IntPart;
	int FloatPart;
	char IntLength;
	char FloatLength;
}fixed_t;

extern const fixed_t ZERO;
/**
* \brief Создание объекта типа fixed_t из числа типа int
* \param a Число, над которым работает программа
* \return Возвращает объект типа fixed_t
*/
fixed_t FixedFromInt(int a);

/**
* \brief Создание объекта типа fixed_t из числа типа double
* \param a Число, над которым работает программа
* \return Возвращает объект типа fixed_t
*/
fixed_t FixedFromDouble(double a);

/**
* \brief Создание числа типа int из объекта типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает число типа int
*/
int FixedAsInt(fixed_t a);

/**
* \brief Создание числа типа double из объекта типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает число типа double
*/
double FixedAsDouble(fixed_t a);

/**
* \brief Создание объекта типа fixed_t из строки вида FIX[x.x]
* \param string Строка, из которой создаётсяя объект
* \return Возвращает объект типа fixed_t
*/
fixed_t FixedParse(char* string);

/**
* \brief Создание строки вида FIX[x.x] из объекта типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает указатель на начало строки
*/
char* FixedFormat(fixed_t a);

/**
* \brief Считывание строки вида FIX[x.x] из файла и преобразование в объект типа fixed_t
* \param filepath Строка, содержащая в себе путь к файлу
* \return Возвращает объект типа fixed_t
*/
fixed_t FixedRead(char const* filepath);

/**
* \brief Преобразует объект типа fixed_t в строку вида FIX[x.x] и записывает его в файл
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \param filepath Строка, содержащая в себе путь к файлу
* \return Возвращает 1, если функция выполнена, и 0, если возникла ошибка
*/
char FixedWrite(fixed_t a, char const* filepath);
/**
* \brief Операция суммирования двух объектов типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \param b Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает результат суммирования в виде объекта типа fixed_t
*/
fixed_t FixedAdd(fixed_t a, fixed_t b);

/**
* \brief Операция вычитания двух объектов типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия (Уменьшаемое)
* \param b Число в виде объекта fixed_t, над которым выполняются действия (Вычитаемое)
* \return Возвращает результат вычитания в виде объекта типа fixed_t
*/
fixed_t FixedSub(fixed_t a, fixed_t b);

/**
* \brief  Операция произведения двух объектов типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \param b Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает результат произведения в виде объекта типа fixed_t
*/
fixed_t FixedMul(fixed_t a, fixed_t b);

/**
* \brief  Операция деление двух объектов типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия (Делимое)
* \param b Число в виде объекта fixed_t, над которым выполняются действия (Делитель)
* \return Возвращает результат деления в виде объекта типа fixed_t
*/
fixed_t FixedDiv(fixed_t a, fixed_t b);

/**
* \brief Взятие объекта типа fixed_t с противоположным знаком
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает результат операции в виде объекта типа fixed_t
*/
fixed_t FixedNegate(fixed_t a);

/**
* \brief Деление 1 на объект типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает результат операции в виде объекта типа fixed_t
*/
fixed_t FixedReciprocal(fixed_t a);

/**
* \brief Получение модуля от объекта типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает результат операции в виде объекта типа fixed_t
*/
fixed_t FixedAbs(fixed_t a);

/**
* \brief Округление объекта типа fixed_t до единиц по правилам математики
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает результат операции в виде объекта типа fixed_t
*/
fixed_t FixedRound(fixed_t a);

/**
* \brief Округление объекта типа fixed_t до единиц в меньшую сторону
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает результат операции в виде объекта типа fixed_t
*/
fixed_t FixedFloor(fixed_t a);

/**
* \brief Округление объекта типа fixed_t до единиц в большую сторону
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает результат операции в виде объекта типа fixed_t
*/
fixed_t FixedCeil(fixed_t a);

/**
* \brief Сравнеение двух объектов типа fixed_t
* \param a Число в виде объекта fixed_t, над которым выполняются действия
* \param b Число в виде объекта fixed_t, над которым выполняются действия
* \return Возвращает -1, если первое число меньше второго, 0, если они равны, 1, если первое число больше второго
*/
char FixedCompare(fixed_t a, fixed_t b);
#endif // !FIXLIB_H