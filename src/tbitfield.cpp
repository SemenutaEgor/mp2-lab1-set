#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = ((len - 1) / 32) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
	{
		char e[] = "Error";
		throw e;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[]pMem;

}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / 32;
}


TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int v;
	v = n % 32;
	TELEM tmp = 1;
	tmp = tmp << v;
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
	{
		int i = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		pMem[i] = (pMem[i] | mask);

	}
	else
	{
		char e[] = "Error";
		throw e;
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
	{
		int i = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		mask = ~mask;
		pMem[i] = (pMem[i] & mask);
	}
	else
	{
		char e[] = "Error";
		throw e;
	}
}

bool TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n < BitLen)
	{
		int i = GetMemIndex(n);
		TELEM mask = GetMemMask(n);
		return(pMem[i] & mask);
	}
	else
	{
		char e[] = "Error";
		throw e;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		if (MemLen != bf.MemLen)
		{
			MemLen = bf.MemLen;
			delete[]pMem;
			pMem = new TELEM[MemLen];
		}
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	BitLen = bf.BitLen;
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return false;
	}
	for (int i = 0; i < MemLen - 1; i++)
	{
		if (pMem[i] != bf.pMem[i])
		{
			return false;
		}
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
		{
			return false;
		}
	}
	return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf) {
		return false;
	}
	else
	{
		return true;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxBitLen = bf.BitLen;
	if (BitLen > bf.BitLen)
	{
		maxBitLen = BitLen;
	}
	TBitField res(maxBitLen);
	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < MemLen - 1; i++)
		{
			res.pMem[i] = pMem[i];
		}
		for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		{
			if (GetBit(i))
			{
				res.SetBit(i);

			}
		}
		for (int i = 0; i < res.MemLen; i++)
		{
			res.pMem[i] = res.pMem[i] | bf.pMem[i];
		}
	}
	else
	{
		for (int i = 0; i < bf.MemLen - 1; i++)
		{
			res.pMem[i] = bf.pMem[i];
		}
		for (int i = (bf.MemLen - 1) * 32; i < bf.BitLen; i++)
		{
			if (bf.GetBit(i))
			{
				res.SetBit(i);

			}
		}
		for (int i = 0; i < res.MemLen; i++)
		{
			res.pMem[i] = res.pMem[i] | pMem[i];
		}
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxBitLen = bf.BitLen;
	if (BitLen > bf.BitLen)
	{
		maxBitLen = BitLen;
	}
	TBitField res(maxBitLen);
	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < MemLen - 1; i++)
		{
			res.pMem[i] = pMem[i];
		}
		for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		{
			if (GetBit(i))
			{
				res.SetBit(i);

			}
		}
		for (int i = 0; i < res.MemLen; i++)
		{
			res.pMem[i] = res.pMem[i] & bf.pMem[i];
		}
	}
	else
	{
		for (int i = 0; i < bf.MemLen - 1; i++)
		{
			res.pMem[i] = bf.pMem[i];
		}
		for (int i = (bf.MemLen - 1) * 32; i < bf.BitLen; i++)
		{
			if (bf.GetBit(i))
			{
				res.SetBit(i);

			}
		}
		for (int i = 0; i < res.MemLen; i++)
		{
			res.pMem[i] = res.pMem[i] & pMem[i];
		}
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);
	for (int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = ~pMem[i];
	}
	return res;
}

istream &operator>>(istream &is, TBitField &bf) {
	char c;
	int k = 0;
	do
	{
		is >> c;
		if (c == '1')
		{
			bf.SetBit(k);
			k++;
		}
		if (c == '0')
		{
			bf.ClrBit(k);
			k++;
		}
		if (k == bf.BitLen)break;
	} while ((c == '1') || (c == '0'));
	return is;
}

ostream &operator<<(ostream &os, const TBitField &bf) {
	for (int i = 0; i < bf.BitLen; i++)
	{
		os << bf.GetBit(i);
	}
	return os;
}
