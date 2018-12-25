// OsadnicyOldSchool.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

inline void RysujPola(int ilosc, int poziom, string wolne = "()", string qs = "    ", string ds = "  ")
{
	for (int i = 0; i < poziom; i++)
	{
		cout << qs << flush;
	}
	for (int i = 0; i < ilosc; i++)
	{
		cout << wolne << ds << ds << ds << flush;
	}
	cout << endl;
}

inline void DrogiKrzyzowe(int ilosc, int poziom, string sl = "//", string bs = "\\\\", string qs = "    ", string ds = "  ")
{
	for (int i = 0; i < poziom - 1; i++)
	{
		cout << qs << flush;
	}
	cout << "   " << flush;
	for (int i = 0; i < ilosc; i++)
	{
		cout << sl << bs << qs;
	}
	cout << endl;

	for (int i = 0; i < poziom - 1; i++)
	{
		cout << qs << flush;
	}
	cout << "  " << flush;
	for (int i = 0; i < ilosc; i++)
	{
		cout << sl << ds << bs << ds << flush;
	}
	cout << endl;

}
inline void DrogiKrzyzoweback(int ilosc, int poziom, string sl = "//", string bs = "\\\\", string qs = "    ", string ds = "  ")
{
	for (int i = 0; i < poziom - 1; i++)
	{
		cout << qs << flush;
	}
	cout << "  " << flush;
	for (int i = 0; i < ilosc; i++)
	{
		cout << bs << ds << sl << ds << flush;
	}
	cout << endl;

	for (int i = 0; i < poziom - 1; i++)
	{
		cout << qs << flush;
	}
	cout << "   " << flush;
	for (int i = 0; i < ilosc; i++)
	{
		cout << bs << sl << qs;
	}
	cout << endl;


}
void DrawBoard(int base, int height)
{
	string sl = "//", bs = "\\\\";
	string wolne = "()";
	string ds = "  ";
	string qs = "    ";
	string droga = "||";
	//cout << sl << " " << bs;
	for (int i = 0; i < height; i++)
	{
		if (i != 0) RysujPola(i + base, height - i);
		if (i != 0) RysujPola(i + base, height - i, droga);
		if (i != 0) RysujPola(i + base, height - i, droga);
		RysujPola(i + base, height - i);
		DrogiKrzyzowe(i + base, height - i);
	}
	for (int i = height; i >= 0; i--)
	{
		RysujPola(i + base, height - i);
		if (i != 0)RysujPola(i + base, height - i, droga);
		if (i != 0) RysujPola(i + base, height - i, droga);
		if (i != 0) RysujPola(i + base, height - i);
		if (i != 0) DrogiKrzyzoweback(i + base - 1, height - i + 1);
	}


}


int main()
{
	int szerokosc = 4;
	int wysokosc = 2;
	int **pola;

	pola = new int*[wysokosc * 2];
	for (int i = 0; i <= wysokosc * 2; i += 2)
	{
		if (i != 0)
		{
			pola[i - 1] = new int[szerokosc + i / 2];
		}
		if (i != 0)
		{
			for (int j = 0; j < szerokosc + i / 2; j++)
			{
				pola[i - 1][j] = 0;
			}
		}
		pola[i] = new int[szerokosc + i / 2];
		for (int j = 0; j < szerokosc + i / 2; j++)
		{
			pola[i][j] = 0;
		}
	}
	//for (int i = wysokosc-1; i > 0;i++)
	//{
	//	pola[wysokosc*2-i] = new int[szerokosc + i];
	//	for (int j = 0; j < szerokosc + i; j++) pola[i][j] = 0;
	//}
	for (int i = 0; i <= wysokosc * 2; i += 2)
	{
		if (i != 0)
		{
			for (int j = 0; j < szerokosc + i / 2; j++)
			{
				cout << i - 1 << "/" << j << ": " << pola[i - 1][j] << "\t";
			}
		}
		cout << endl;
		for (int j = 0; j < szerokosc + i / 2; j++) cout << i << "/" << j << ": " << pola[i][j] << "\t";
		cout << endl;
	}

	DrawBoard(szerokosc, wysokosc);
}

