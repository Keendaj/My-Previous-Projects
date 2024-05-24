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
* \return ���������� ������ ���� fixed_t
*/
fixed_t FixedFromInt(int a);

/**
* \brief �������� ������� ���� fixed_t �� ����� ���� double
* \param a �����, ��� ������� �������� ���������
* \return ���������� ������ ���� fixed_t
*/
fixed_t FixedFromDouble(double a);

/**
* \brief �������� ����� ���� int �� ������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ����� ���� int
*/
int FixedAsInt(fixed_t a);

/**
* \brief �������� ����� ���� double �� ������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ����� ���� double
*/
double FixedAsDouble(fixed_t a);

/**
* \brief �������� ������� ���� fixed_t �� ������ ���� FIX[x.x]
* \param string ������, �� ������� ��������� ������
* \return ���������� ������ ���� fixed_t
*/
fixed_t FixedParse(char* string);

/**
* \brief �������� ������ ���� FIX[x.x] �� ������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �� ������ ������
*/
char* FixedFormat(fixed_t a);

/**
* \brief ���������� ������ ���� FIX[x.x] �� ����� � �������������� � ������ ���� fixed_t
* \param filepath ������, ���������� � ���� ���� � �����
* \return ���������� ������ ���� fixed_t
*/
fixed_t FixedRead(char const* filepath);

/**
* \brief ����������� ������ ���� fixed_t � ������ ���� FIX[x.x] � ���������� ��� � ����
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \param filepath ������, ���������� � ���� ���� � �����
* \return ���������� 1, ���� ������� ���������, � 0, ���� �������� ������
*/
char FixedWrite(fixed_t a, char const* filepath);
/**
* \brief �������� ������������ ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� ������������ � ���� ������� ���� fixed_t
*/
fixed_t FixedAdd(fixed_t a, fixed_t b);

/**
* \brief �������� ��������� ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� �������� (�����������)
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� �������� (����������)
* \return ���������� ��������� ��������� � ���� ������� ���� fixed_t
*/
fixed_t FixedSub(fixed_t a, fixed_t b);

/**
* \brief  �������� ������������ ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� ������������ � ���� ������� ���� fixed_t
*/
fixed_t FixedMul(fixed_t a, fixed_t b);

/**
* \brief  �������� ������� ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� �������� (�������)
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� �������� (��������)
* \return ���������� ��������� ������� � ���� ������� ���� fixed_t
*/
fixed_t FixedDiv(fixed_t a, fixed_t b);

/**
* \brief ������ ������� ���� fixed_t � ��������������� ������
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixedNegate(fixed_t a);

/**
* \brief ������� 1 �� ������ ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixedReciprocal(fixed_t a);

/**
* \brief ��������� ������ �� ������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixedAbs(fixed_t a);

/**
* \brief ���������� ������� ���� fixed_t �� ������ �� �������� ����������
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixedRound(fixed_t a);

/**
* \brief ���������� ������� ���� fixed_t �� ������ � ������� �������
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixedFloor(fixed_t a);

/**
* \brief ���������� ������� ���� fixed_t �� ������ � ������� �������
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� ��������� �������� � ���� ������� ���� fixed_t
*/
fixed_t FixedCeil(fixed_t a);

/**
* \brief ���������� ���� �������� ���� fixed_t
* \param a ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \param b ����� � ���� ������� fixed_t, ��� ������� ����������� ��������
* \return ���������� -1, ���� ������ ����� ������ �������, 0, ���� ��� �����, 1, ���� ������ ����� ������ �������
*/
char FixedCompare(fixed_t a, fixed_t b);
#endif // !FIXLIB_H