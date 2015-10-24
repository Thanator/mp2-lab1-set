// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

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

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	return BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return (*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
	int check = 1;
	if (MaxPower == s.MaxPower)
	{
		for (int i = 0; i < BitField.GetLength(); i++)
		{
			if (BitField.GetBit(i) != s.BitField.GetBit(i))
			{
				check = 0;
				break;
			}
		}
	}
	else
	{
		check = 0;
	}
	return check;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int check = 0;
	if (MaxPower == s.MaxPower)
	{
		for (int i = 0; i < BitField.GetLength(); i++)
		{
			if (BitField.GetBit(i) != s.BitField.GetBit(i))
			{
				check = 1;
				break;
			}
		}
	}
	else
	{
		check = 1;
	}
	return check;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int maxlength = MaxPower;
	if (MaxPower < s.MaxPower)
		maxlength = s.MaxPower;
	TSet A(maxlength);
	A.BitField = BitField | s.BitField;
	return A;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet A(MaxPower);
	if ((Elem < MaxPower) && (Elem > -1))
		A.BitField.SetBit(Elem);
	else throw Elem;
	return A;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet A(MaxPower);
	if ((Elem < MaxPower) && (Elem > -1))
		A.BitField.ClrBit(Elem);
	else throw Elem;
	return A;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int maxlength = MaxPower;
	if (MaxPower < s.MaxPower)
		maxlength = s.MaxPower;
	TSet A(maxlength);
	A.BitField = BitField & s.BitField;
	return A;
}

TSet TSet::operator~(void) // дополнение
{
	TSet A(MaxPower);
	A.BitField = ~BitField;
	return A;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int k;
	while (1)
	{
		istr >> k;
		if ((k < s.GetMaxPower()) && (k > -1))
			s.InsElem(k);
		else break;

	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		if (s.IsMember(i))
			ostr << i << " ";
	}
	return ostr;
}

