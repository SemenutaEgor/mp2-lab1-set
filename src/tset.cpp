// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField (mp), MaxPower (mp) /*BitField(-1)*/
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField (s.BitField), MaxPower (s.MaxPower) /*BitField(-1)*/
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower (bf.GetLength()), BitField(bf) /*BitField(-1)*/
{
}
// Оператор преобразования типа к BitField
TSet::operator TBitField() 
{
	TBitField temp(this->BitField);
	return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.GetMaxPower();
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower)
		return BitField != s.BitField;
	else
		return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField c = BitField | s.BitField;
	TSet res(c);
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(MaxPower) ;
	res.InsElem(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(MaxPower);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField c = BitField & s.BitField;
	TSet res(c);
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(~BitField);
	return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int a;
	istr >> a;
	while (a >= 0) {
		s.InsElem(a);
		istr >> a;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.IsMember(i))
			ostr << ' ' << i << ' ';
	return ostr;
}
