/**
* \file
 * \brief ���������� ������ ���� ������ fixed_t: ����� � ������������� ������
 */
#ifndef FIXLIB_H
#define FIXLIB_H

/** 
* \param IntPart ������������� ����� �����
* \param FloatPart ������������ ����� �����
* \param IntLength ����� ������������� �����
* \param FloatLength ����� ������������ �����
*/
typedef struct {
	int IntPart;
	int FloatPart;
	char IntLength;
	char FloatLength;
}fixed_t;

extern const fixed_t ZERO;
/**
* \brief �������� ������� ���� fixed_t �� ����� ���� int
* \param a �����, ��� ������� �������� ���������
* \return ���������� ������ ���� fixed_t*/ 
fixed_t FixFromInt(int a);

/**
* \brief �������� ������� ���� fixed_t �� ����� ���� double
* \param a �����, ��� ������� �������� ���������
* \return ���������� ������ ���� fixed_t
*/
fixed_t FixFromDouble(double a);

/**
* \brief �������� ����� ���� int �� ������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ����� ���� int
*/
int FixAsInt(fixed_t a);

/**
* \brief �������� ����� ���� double �� ������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ����� ���� double
*/
double FixAsDouble(fixed_t a);

/**
* \brief �������� ������� ���� fixed_t �� ������ ���� FIX[x.x]
* \param string ������, �� ������� ��������� ������
* \return ���������� ������ ���� fixed_t
*/
fixed_t FixParse(char* string);

/**
* \brief �������� ������ ���� FIX[x.x] �� ������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �� ������ ������
*/
char* FixFormat(fixed_t a);

/**
* \brief ���������� ������ ���� FIX[x.x] �� ����� � �������������� � ������ ���� fixed_t
* \param filepath ������, ���������� � ���� ���� � �����
* \return ���������� ������ ���� fixed_t
*/
fixed_t FixRead(char const* filepath);

/**
* \brief ����������� ������ ���� fixed_t � ������ ���� FIX[x.x] � ���������� ��� � ����
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \param filepath ������, ���������� � ���� ���� � �����
* \return ���������� 1, ���� ������� ���������, � 0, ���� �������� ������
*/
char FixWrite(fixed_t a, char const* filepath);
/**
* \brief �������� ������������ ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� ������������ � ���� ������� ���� fixed_t
*/
fixed_t FixAdd(fixed_t a, fixed_t b);

/**
* \brief �������� ��������� ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� �������� (�����������)
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� �������� (����������)
* \return ���������� ��������� ��������� � ���� ������� ���� fixed_t
*/
fixed_t FixSub(fixed_t a, fixed_t b);

/**
* \brief  �������� ������������ ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� ������������ � ���� ������� ���� fixed_t
*/
fixed_t FixMul(fixed_t a, fixed_t b);

/**
* \brief  �������� ������� ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� �������� (�������)
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� �������� (��������)
* \return ���������� ��������� ������� � ���� ������� ���� fixed_t
*/
fixed_t FixDiv(fixed_t a, fixed_t b);

/**
* \brief ������ ������� ���� fixed_t � ��������������� ������
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixNegate(fixed_t a);

/**
* \brief ������� 1 �� ������ ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixReciprocal(fixed_t a);

/**
* \brief ��������� ������ �� ������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixAbs(fixed_t a);

/**
* \brief ���������� ������� ���� fixed_t �� ������ �� �������� ����������
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixRound(fixed_t a);

/**
* \brief ���������� ������� ���� fixed_t �� ������ � ������� �������
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixFloor(fixed_t a);

/**
* \brief ���������� ������� ���� fixed_t �� ������ � ������� �������
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixCeil(fixed_t a);

/**
* \brief ���������� ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� -1, ���� ������ ����� ������ �������, 0, ���� ��� �����, 1, ���� ������ ����� ������ �������
*/
char FixCompare(fixed_t a, fixed_t b);
#endif // !FIXLIB_H