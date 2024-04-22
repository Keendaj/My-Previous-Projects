#ifndef LABENGINE_H_INCLUDED
#define LABENGINE_H_INCLUDED
#pragma once

/**
 * @mainpage Introduction
 
LabEngine представляет собой простейшую графическую библиотеку для проведения
лабораторных работ в рамках консольных приложений для Windows. Она позволяет
на первых порах, не вдаваясь в организацию оконных приложений и правила борьбы
с WinAPI, делать несложные лабораторные с применением графики.

Минимальная программа с использованием библиотеки выглядит следующим образом:

@code{.c}
#include "labengine.h"

int main(void)
{
  if (LabInit())    // Инициализация
  {
    // ...          // Здесь можно что-то сделать

    LabTerm();      // Завершение работы
  }
  return 0;
}
@endcode

Эта программа инициализирует библиотеку и, в случае успеха, сразу же завершает
работу программы. Можно успеть заметить, как открывается окно для рисования, но
тут же закрывается.

Более осмысленная версия программы выглядит так:

@code
#include "labengine.h"

int main(void)
{
  // Инициализировать библиотеку
  if (LabInit())
  {
    // Узнать размеры окна
    int width = LabGetWidth();
    int height = LabGetHeight();
  
    // Нарисовать красный прямоугольник
    LabSetColor(LABCOLOR_RED);
    LabDrawRectangle(0, 0, width, height);
    
    // Нарисовать зелёный крест
    LabSetColor(LABCOLOR_GREEN);
    LabDrawLine(1, 1, width - 1, height - 1);
    LabDrawLine(1, height - 2, width - 1, 0);

    // Отобразить картинку в окне
    LabDrawFlush();

    // Подождать нажатия клавиши и закончить работу
    LabInputKey();
    LabTerm();
  }
  return 0;
}
@endcode

Обратите внимание на координаты (ноль --- в левом верхнем углу). По принятому
в Windows соглашению конечные точки линий и прямоугольников не рисуются (линии
не доходят до указанных координат).

Результат выполнения программы:

@image html basics.png

*/

#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")

#if defined(_DEBUG) || !defined(NDEBUG)
#define LABENGINE_LIB_SUFFIX "-dbg"
#else
#define LABENGINE_LIB_SUFFIX
#endif

#ifdef _MSC_VER
#if   _MSC_VER >= 1900 // Visual Studio 2015
#pragma comment(lib, "labengine-vs15" LABENGINE_LIB_SUFFIX)
#elif _MSC_VER >= 1800 // Visual Studio 2013
#pragma comment(lib, "labengine-vs13" LABENGINE_LIB_SUFFIX)
#elif _MSC_VER >= 1700 // Visual Studio 2012
#pragma comment(lib, "labengine-vs12" LABENGINE_LIB_SUFFIX)
#elif _MSC_VER >= 1600 // Visual Studio 2010
#pragma comment(lib, "labengine-vs10" LABENGINE_LIB_SUFFIX)
#elif _MSC_VER >= 1500 // Visual Studio 2008
#pragma comment(lib, "labengine-vs08" LABENGINE_LIB_SUFFIX)
#else
#error This Visual Studio version is not supported.
#endif
#else
#error This compiler is not supported.
#endif

#undef LABENGINE_LIB_SUFFIX

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Логический тип.
 *
 * В языке Си отсутствует выделенный булевский (логический) тип, и вместо
 * него используется тип int. Чтобы избежать этой потери семантики значений,
 * библиотека предоставляет данное перечисление.
 */
typedef enum labbool_t
{
  LAB_FALSE, ///< Ложь (0)
  LAB_TRUE   ///< Истина (1)
} labbool_t;

/**
 * @defgroup lifecycle_group Lifecycle Methods
 *
 * Функции инициализации графического режима и окончания работы в нём.
 *
 * @{
 */

/**
 * Параметры инициализации библиотеки.
 *
 * Используются при вызове функции LabInitWith(). При вызове LabInit()
 * параметры не указывается, используются некоторые значения по умолчанию.
 */
typedef struct labparams_t
{
  unsigned width;  ///< ширина буфера для рисования
  unsigned height; ///< высота буфера для рисования
  unsigned scale;  ///< коэффициент масштабирования буфера при выводе на экран
} labparams_t;

/**
 * @brief Инициализировать библиотеку.
 * 
 * Перед работой с другими функциями библиотеки необходимо её инициализировать.
 * При этом заполняются внутренние структуры данных, создаётся графическое
 * окно. При необходимости задать параметры, отличные от настроек по умолчанию,
 * следует пользоваться функцией LabInitWith().
 * По окончании работы с библиотекой необходим вызов LabTerm().
 * 
 * @return @ref LAB_TRUE если инициализация прошла успешно, иначе - @ref LAB_FALSE.
 * @see LabInitWith, LabTerm
 */
labbool_t LabInit(void);

/**
 * @brief Инициализировать библиотеку с параметрами.
 *
 * Перед работой с другими функциями библиотеки необходимо её инициализировать.
 * При этом заполняются внутренние структуры данных, создаётся графическое
 * окно. Если нет необходимости задавать параметры, отличные от настроек по умолчанию,
 * следует пользоваться функцией LabInit().
 * По окончании работы с библиотекой необходим вызов LabTerm().
 *
 * @param params параметры инициализации библиотеки
 *
 * @return @ref LAB_TRUE если инициализация прошла успешно, иначе - @ref LAB_FALSE.
 * @see LabInit, LabTerm
 */
labbool_t LabInitWith(labparams_t const* params);

/**
 * @brief Завершить работу c библиотекой.
 * 
 * Необходим вызов для окончания работы в графическом режиме и закрытия 
 * окна графического режима.
 * Перед началом работы в графическом режиме необходим вызов LabInit().
 *
 * @see LabInit, LabInitWith
 */
void LabTerm(void);

/**
 * @brief Приостанавить исполнение программы.
 * 
 * @param time количество миллисекунд
 */
void LabDelay(int time);

/**@}*/


/**
 * @defgroup graphics_group Graphics Methods
 *
 * Функции графического вывода и получения информации об окне.
 * Подробнее о группе: @ref graphics_group
 * @{
 */

/**
 * @brief Названия цветов цветовой палитры.
 *
 * Используются для назначения цвета линий и других графических объектов.
 * Передаются в качестве параметра в функцию LabSetColor().
 *
 * @see LabSetColor
 */
typedef enum labcolor_t 
{ 
  LABCOLOR_NA = -1,       ///< Цвет неопределён

  LABCOLOR_BLACK,         ///< Чёрный
  LABCOLOR_DARK_BLUE,     ///< Тёмно-синий
  LABCOLOR_DARK_GREEN,    ///< Тёмно-зелёный
  LABCOLOR_DARK_CYAN,     ///< Тёмно-голубой
  LABCOLOR_DARK_RED,      ///< Тёмно-красный
  LABCOLOR_DARK_MAGENTA,  ///< Тёмно-пурпурный
  LABCOLOR_BROWN,         ///< Коричневый
  LABCOLOR_LIGHT_GREY,    ///< Светло-серый
  LABCOLOR_DARK_GREY,     ///< Тёмно-серый
  LABCOLOR_BLUE,          ///< Синий
  LABCOLOR_GREEN,         ///< Зелёный
  LABCOLOR_CYAN,          ///< Голубой
  LABCOLOR_RED,           ///< Красный
  LABCOLOR_MAGENTA,       ///< Пурпурный
  LABCOLOR_YELLOW,        ///< Жёлтый
  LABCOLOR_WHITE,         ///< Белый

  LABCOLOR_COUNT,         ///< Количество цветов в палитре
} labcolor_t;

/**
 * @brief Узнать ширину окна.
 * 
 * @return ширина графического окна.
 * @see LabGetHeight
 */
int LabGetWidth(void);

/**
 * @brief Узнать высоту окна.
 * 
 * @return высота графического окна.
 * @see LabGetWidth
 */
int LabGetHeight(void);

/**
 * @brief Очистить окно.
 *
 * Для очистки используется чёрный цвет. При желании можно быстро
 * очищать окно другим цветом, воспользовавшись функцией LabClearWith().
 *
 * @see LabClearWith
 */
void LabClear();

/**
 * @brief Очистить окно заданным цветом.
 * 
 * @param color цвет, которым проливается экран
 * @see LabClear
 */
void LabClearWith(labcolor_t color);

/**
 * @brief Установить текущий цвет.
 *
 * Позволяет задать один из цветов стандартной палитры в качестве текущего,
 * используемого для последующего рисования графических объектов
 * функциями <code>LabDraw...()</code>.
 * По умолчанию (до первого вызова этой функции) используется белый цвет
 * (@ref LABCOLOR_WHITE).
 *
 * @param color новый цвет из перечисления <code>labcolor_t</code>.
 * @see labcolor_t, LabSetColorRGB()
 */
void LabSetColor(labcolor_t color);

/** 
 * @brief Установить текущий цвет по компонентам.
 *
 * Позволяет выбрать один из 16,777,216 цветов в качестве текущего,
 * используемого для последующего рисования графических объектов
 * функциями <code>LabDraw...()</code>. Стандартная палитра при этом
 * игнорируется, цвет составляется как комбинация яркостей отдельных
 * компонент (каналов) - красной, зелёной и синей, в пределах от
 * 0 (отсутствие компонены) до 255 (максимальная яркость компоненты).
 *
 * Поскольку выбранный цвет не обязательно принадлежит стандартной
 * палитре, функция LabGetColor() будет возвращать @ref LABCOLOR_NA.
 *
 * @param r яркость красной компоненты, от 0 до 255.
 * @param g яркость зелёной компоненты, от 0 до 255.
 * @param b яркость синей компоненты, от 0 до 255.
 *
 * @see LabSetColor
 */
void LabSetColorRGB(int r, int g, int b);

/** 
 * @brief Узнать текущий цвет.
 *
 * @return текущий цвет из стандартной палитры, используемый для рисования
 * функциями <code>LabDraw...()</code>.
 */
labcolor_t LabGetColor(void);


/** 
 * @brief Нарисовать прямую линию.
 *
 * Рисование линии, соединяющей точки с координатами (x1, y1) и (x2, y2).
 * Последняя точка не рисуется.
 *
 * @param x1 горизонтальная координата первой точки (0 слева)
 * @param y1 вертикальная координата первой точки (0 сверху)
 * @param x2 горизонтальная координата второй точки
 * @param y2 вертикальная координата второй точки.
 */
void LabDrawLine(int x1, int y1, int x2, int y2);

/** 
 * @brief Нарисовать точку.
 *
 * Рисование точки с координатами (x, y).
 *
 * @param x горизонтальная координата точки
 * @param y вертикальная координата точки.
 */
void LabDrawPoint(int x, int y);

/** 
 * @brief Нарисовать прямоугольник.
 *
 * Рисование прямоугольника с левым верхним и правым нижним углами 
 * с координатами (x1, y1) и (x2, y2) соответственно.
 *
 * @param x1 горизонтальная координата левого верхнего угла
 * @param y1 вертикальная координата левого верхнего угла
 * @param x2 горизонтальная координата правого нижнего угла
 * @param y2 вертикальная координата правого нижнего угла.
 */
void LabDrawRectangle(int x1, int y1, int x2, int y2);

/** 
 * @brief Нарисовать окружность.
 *
 * Рисование окружности с координатами центра (x, y) и радиусом radius.
 *
 * @param x горизонтальная координата центра окружности
 * @param y вертикальная координата центра
 * @param radius радиус окружности.
 */
void LabDrawCircle(int x, int y, int radius);

/** 
 * @brief Нарисовать эллипс.
 *
 * Рисование эллипса с координатами центра (x, y) и полуосями a и b.
 *
 * @param x горизонтальная координата центра эллипса
 * @param y вертикальная координата центра
 * @param a большая полуось
 * @param b малая полуось.
 */
void LabDrawEllipse(int x, int y, int a, int b);

/**
 * @brief Насильно отобразить буфер рисования на экран.
 *
 * Когда выполняются команды <code>LabDraw...()</code>, для обеспечения
 * лучшей производительности они рисуют не напрямую на экране, а во
 * вспомогательном буфере в памяти. На экран содержимое этого буфера
 * попадает только тогда, когда этого требует операционная система,
 * либо при явном вызове этой функции.
 *
 * Типичное использование этой функции заключается в предварительной подготовке
 * полного изображения в памяти с последующим однократным отображением
 * его на экран. При наличии анимации в программе необходимо вызывать данную
 * функцию после построения каждого кадра.
 *
 */
void LabDrawFlush(void);

/**@}*/


/**
 * @defgroup input_group Input Methods
 *
 * Группа функций, обеспечивающая возможность работы с клавиатурой.
 * Подробнее о группе: @ref input_group
 * @{
 */

/**
 * @brief Коды несимвольных клавиш.
 *
 * Специальные коды для клавиш Enter, Escape, стрелок...
 * Наряду с ASCII-кодами символьных клавиш, являются возвращаемым значением
 * из функции LabInputKey().
 *
 * @see LabInputKey
 */
typedef enum labkey_t
{ 
  LABKEY_ENTER = 0x0D00,      ///< Enter 
  LABKEY_ESC = 0x1B00,        ///< Escape 
  LABKEY_BACK = 0x0800,       ///< Backspace 
  LABKEY_TAB = 0x0900,        ///< Tab 
  LABKEY_PAGE_UP = 0x2100,    ///< PageUp 
  LABKEY_PAGE_DOWN = 0x2200,  ///< PageDown 
  LABKEY_LEFT = 0x2500,       ///< Стрелка влево
  LABKEY_UP = 0x2600,         ///< Стрелка вверх
  LABKEY_RIGHT = 0x2700,      ///< Стрелка вправо
  LABKEY_DOWN = 0x2800,       ///< Стрелка вниз
 
} labkey_t;

/**
 * @brief Ожидать нажатия клавиши и узнать её код.
 * 
 * Ожидает нажатия клавиши, а затем, когда клавиша нажата, возвращает её код -
 * ASCII-код для символьных клавиш или код из перечисления <code>labkey_t</code>
 * для несимвольных клавиш (такий как Enter, Escape, стрелки ... ).
 *
 * @return код нажатой клавиши.
 * @see labkey_t
 */
labkey_t LabInputKey(void);

/**
 * Проверить наличие необработанных нажатий клавиш.
 *
 * @return @ref LAB_TRUE если есть необработанные нажатия клавиш, @ref LAB_FALSE, если таких нет.
 */
labbool_t LabInputKeyReady(void);

/** @}*/


#ifdef __cplusplus
}
#endif

#endif // LABENGINE_H_INCLUDED
