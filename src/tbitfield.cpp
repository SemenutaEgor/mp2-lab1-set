// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (BitLen / 32) + 1;
	pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n >> 4;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 16);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[i] = pMem[i] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	mask = ~mask;
	pMem[i] &= mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int i = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	return pMem[i] & mask;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen) {
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return false;
	for (int i = 0; i < MemLen - 1; i++)
		if (pMem[i] != bf.pMem[i])
			return false;
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		if (GetBit(i) != bf.GetBit(i))
			return false;
	return true;
}

/*int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return 0;
}*/

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField tmp(len);
	for (i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] |= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
		len = bf.BitLen;
	TBitField tmp(len);
	for (i = 0; i < MemLen; i++)
		tmp.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++)
		tmp.pMem[i] &= bf.pMem[i];
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bf(BitLen);
	for (int i = 0; i < MemLen; i++)
		bf.pMem[i] = ~pMem[i];
	return bf;
}

// ввод/вывод

istream &operator>>(istream &is, TBitField &bf) // ввод
{
	char c;
	int k = 0;
	do {
		is >> c;
		if (c == '1')
			bf.SetBit(k);
		if (c == '0')
			bf.ClrBit(k);
		k++;
	} while ((c == '1') || (c == '0'));
	return is;
}

ostream &operator << (ostream &os, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		if (bf.GetBit(i) != 0)
			os << 1;
		else
			os << 0;
	return os;
}
