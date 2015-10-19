// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (BitLen / sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw len;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int k = n % (sizeof(TELEM) * 8);
	TELEM M = 1;
	M = M << k;
	return M;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{

	if ((n > -1) && (n < BitLen))
	{
		int index = GetMemIndex(n);
		TELEM Mask = GetMemMask(n);
		pMem[index] |= Mask;
	}
	else
		throw n;


}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
	{
		int index = GetMemIndex(n);
		TELEM Mask = GetMemMask(n);
		pMem[index] &= ~Mask;
	}
	else
		throw n;



}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int res = 0;
	if ((n > -1) && (n < BitLen))
	{
		int index = GetMemIndex(n);
		TELEM Mask = GetMemMask(n);
		if (Mask == (Mask & pMem[index]))
			res = 1;

	}
	else
		throw n;
	return res;




}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];

	}
	return (*this);



}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int check = 1;
	if (BitLen != bf.BitLen)
		check = 0;
	else
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
			{
				check = 0;
				break;
			}
		}
	}
	return check;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int check = 0;
	if (BitLen != bf.BitLen)
		check = 1;
	else
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
			{
				check = 1;
				break;
			}
		}
	}
	return check;

}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxlen = BitLen;
	if (maxlen < bf.BitLen)
		maxlen = bf.BitLen;
	TBitField Res(maxlen);
	for (int i = 0; i < MemLen; i++)
		Res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Res.pMem[i] |= bf.pMem[i];
	return Res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxlen = BitLen;
	if (maxlen < bf.BitLen)
		maxlen = bf.BitLen;
	TBitField Res(maxlen);
	for (int i = 0; i < MemLen; i++)
		Res.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Res.pMem[i] &= bf.pMem[i];
	return Res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField A(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)
			A.SetBit(i);

	}
	return A;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int k;
	for (int i = 0; i < bf.GetLength(); i++)
	{
		istr >> k;
		if (k == 1)
			bf.SetBit(i);
		else if (k == 0)
		{
			bf.ClrBit(i);
		}
		else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
		ostr << bf.GetBit(i) << " ";
	return ostr;

}