// OsadnicyOldSchool.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;
constexpr int szerokosc = 3;
constexpr int wysokosc = 3;
constexpr int wys = 4 * wysokosc; //12
constexpr int szer = szerokosc + wysokosc;//6
constexpr int iloscGraczy = 3;

struct Player
{
	int nr = 0;

};
struct Lad
{
	int trigger = 0;
	char zloze = 's';
};
void tworzLady(Lad tl[wysokosc * 2 - 1][szerokosc + wysokosc])  //na poczatek recznie plansza dla noobow
{
	tl[0][0].trigger = 4;
	tl[0][1].trigger = 6;
	tl[0][2].trigger = 9;
	tl[1][0].trigger = 2;
	tl[1][1].trigger = 5;
	tl[1][2].trigger = 12;
	tl[1][3].trigger = 4;
	tl[2][0].trigger = 9;
	tl[2][1].trigger = 8;
	tl[2][2].trigger = 0;
	tl[2][3].trigger = 8;
	tl[2][4].trigger = 10;
	tl[3][0].trigger = 3;
	tl[3][1].trigger = 5;
	tl[3][2].trigger = 10;
	tl[3][3].trigger = 11;
	tl[4][0].trigger = 3;
	tl[4][1].trigger = 6;
	tl[4][2].trigger = 11;
	tl[0][0].zloze = tl[0][2].zloze = tl[4][0].zloze = tl[4][1].zloze = 'Z';
	tl[0][1].zloze = tl[1][1].zloze = tl[3][0].zloze = tl[3][3].zloze = 'D';
	tl[1][0].zloze = tl[2][1].zloze = tl[3][2].zloze = 'C';
	tl[1][2].zloze = tl[1][3].zloze = tl[2][0].zloze = tl[2][4].zloze = 'O';
	tl[2][3].zloze = tl[3][1].zloze = tl[4][2].zloze = 'K';

}
void zerowanieStartowe(int tablicaM[wys][szer])
{
	for (int i = 0; i < wys; i++) //zapełnianie całej tablicy 9 (oznaka odczytu ze złego miejsca w tablicy)
	{
		for (int j = 0; j < szer; j++)
		{
			tablicaM[i][j] = 9;
		}
	}
	for (int i = 0; i <= wysokosc * 2; i += 2) // zera w pierwszej czesci tablicy
	{
		if (i != 0)
		{
			for (int j = 0; j < szerokosc + i / 2; j++) tablicaM[i - 1][j] = 0;

		}
		for (int j = 0; j < szerokosc + i / 2; j++) tablicaM[i][j] = 0;
	}
	for (int i = 0; i <= wysokosc * 2 - 2; i += 2) //zera w drugiej czesci tablicy
	{
		for (int j = 0; j < szerokosc + wysokosc - i / 2 - 1; j++) tablicaM[wysokosc * 2 + i + 1][j] = 0;
		if (i != wysokosc * 2 - 2)
		{
			for (int j = 0; j < szerokosc + wysokosc - i / 2 - 1; j++) tablicaM[wysokosc * 2 + i + 2][j] = 0;
		}
	}
}
inline void rysujMiejsca(int ilosc, int poziom, int kolumna[szer], string qs = "    ", string ds = "  ")
{
	string wolne;
	for (int i = 0; i < poziom; i++)
	{
		cout << qs << flush;
	}
	for (int i = 0; i < ilosc; i++)
	{
		if (kolumna[i] == 0) wolne = "()";
		if (kolumna[i] == 1) wolne = "M1";
		if (kolumna[i] == 2) wolne = "M2";
		if (kolumna[i] == 3) wolne = "M3";
		if (kolumna[i] == 5) wolne = "||";
		if (kolumna[i] == 9) wolne = "ER";
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
void narysujPlansze(int base, int height, int tablica[wys][szer])
{
	string sl = "//", bs = "\\\\";
	string wolne = "()";
	string ds = "  ";
	string qs = "    ";
	string droga = "||";
	int tempDroga[6] = { 5,5,5,5,5,5 };
	//cout << sl << " " << bs;
	for (int i = 0; i < height; i++) // miasta koncza sie na indeksie nr. 4
	{
		if (i != 0) rysujMiejsca(i + base, height - i, tablica[i * 2 - 1]);
		//if (i != 0) rysujMiejsca(i + base, height - i, tempDroga);
		if (i != 0) rysujMiejsca(i + base, height - i, tempDroga);
		rysujMiejsca(i + base, height - i, tablica[i * 2]);
		DrogiKrzyzowe(i + base, height - i);
	}
	for (int i = height; i >= 0; i--) // od 5. do 12
	{
		rysujMiejsca(i + base, height - i, tablica[height * 4 - i * 2 - 1]);
		//if (i != 0)rysujMiejsca(i + base, height - i, tempDroga);
		if (i != 0) rysujMiejsca(i + base, height - i, tempDroga);
		if (i != 0) rysujMiejsca(i + base, height - i, tablica[height * 4 - i * 2]);
		if (i != 0) DrogiKrzyzoweback(i + base - 1, height - i + 1);
	}


}
void wypiszTabliceTest(int tablica[wys][szer]) // funkcja do testów
{
	for (int i = 0; i < wys; i++)
	{
		for (int j = 0; j < szer; j++)
		{
			cout << i << ":" << j << "  " << tablica[i][j] << "   ";
		}
		cout << endl;
	}
}
void wypiszLadyTest(Lad tl[wysokosc * 2 - 1][szerokosc + wysokosc])
{
	for (int i = 0; i < wysokosc * 2 - 1; i++)
	{
		for (int j = 0; j < szerokosc + wysokosc; j++)
			cout << tl[i][j].trigger << "/" << tl[i][j].zloze << "\t";
		cout << endl;
	}


}
//void postawMiasto

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	unsigned k1, k2;
	//k1 = rand() % 6 + 1;
	//k2 = rand() % 6 + 1;
	int win = 0;
	int nrGracza = 1;
	int PZMax = 0;
	//cout << "k1: " << k1 << " k2: " << k2 << endl;
	int tablicaMiejsc[wys][szer];
	Lad tablicaLadow[wysokosc * 2 - 1][szerokosc + wysokosc];
	tworzLady(tablicaLadow);




	/*
	pola = new int*[wysokosc * 4];

	for (int i = 0; i <= wysokosc * 2; i += 2)
	{
		if (i != 0)
		{
			pola[i - 1] = new int[szerokosc + i / 2];
		}
		pola[i] = new int[szerokosc + i / 2];

		if (i != 0)
		{
			for (int j = 0; j < szerokosc + i / 2; j++)
			{
				pola[i - 1][j] = 0;
			}
		}

		for (int j = 0; j < szerokosc + i / 2; j++)
		{
			pola[i][j] = 0;
		}
	}
	/*
	for (int i = 0;i<= wysokosc * 2 - 2; i += 2)
	{
		pola[wysokosc * 2 + i] = new int[szerokosc + wysokosc - i / 2];
		if (i != wysokosc * 2 - 2)
		{
			pola[wysokosc * 2 + i + 1] = new int[szerokosc + wysokosc - 1 / 2];
		}

	}
	*/
	zerowanieStartowe(tablicaMiejsc);


	//wypiszLadyTest(tablicaLadow);
	//wypiszTabliceTest(tablicaMiejsc);

	cout << "Cześć, mam nadzieję, że gracie we 3, bo jak nie to zagadaj do Magica - on zmieni.." << endl;
	cout << "Do ilu punktów zwycięstwa gramy?";
	cin >> PZMax;
	PZMax = 10; //- to jest do wyrzucenia żeby móc wybierać

	/*Ustawienie początkowe*/
	for (int i = 1; i <= iloscGraczy; i++)
	{
		narysujPlansze(szerokosc, wysokosc, tablicaMiejsc);
		int x=0, y=0;
		cout << "Gracz " << i + 1 << " : Postaw miasto:" << endl
			<< " W którym rzędzie? (mozliwe: 1-" << wysokosc*4<<endl;
		cin >> x;
		x--;
		cout << "Ktore miasto?";//tutaj wrzucic które miasta sa dostepne
		cin >> y;
		y--;
		tablicaMiejsc[x][y] = i;
	}


	/* kolejka*/
	do
	{
		int wybor = 0;
		//system("CLS");
		//wypiszTabliceTest(tablicaMiejsc);
		narysujPlansze(szerokosc, wysokosc, tablicaMiejsc);
		cout << "Co chcesz zrobić?" << endl;



			nrGracza += 1;
		if (nrGracza > iloscGraczy) nrGracza = 1;
	} while (win != 0);
}

