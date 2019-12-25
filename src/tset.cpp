#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

bool TSet::IsMember(const int Elem) const // элемент множества?
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
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
	{
		return false;
	}
	if (BitField != s.BitField)
	{
		return false;
	}
	return true;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (s == *this)
	{
		return false;
	}
	return true;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField temp(*this);
	temp = temp | s.BitField;
	TSet res(temp);
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(*this);
	res.InsElem(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(*this);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField temp(*this);
	temp = temp & s.BitField;
	TSet res(temp);
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	istr >> i;
	while (i >= 0)
	{
		s.InsElem(i);
		istr >> i;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "{";
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i))
		{
			ostr << i << " ";
		}
	}
	ostr << "}";
	return ostr;
}
