﻿#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "io.h"
#include "player.h"
#include "lad.h"

//using namespace std;
using std::cin;
using std::cout;
using std::srand;
using std::vector;
using std::string;
using std::flush;
using std::endl;

constexpr int szerokosc = 3;
constexpr int wysokosc = 3;
constexpr int iloscGraczy = 2;

void tworzLady(vector<vector<Lad>> &tl)  //na poczatek recznie plansza dla noobow
{
	for (int i = 0; i < wysokosc; i++) {
		vector<Lad> wiersz(szerokosc + i);
		tl.push_back(wiersz);
	}
	for (int i = wysokosc - 1; i > 0; i--) {
		vector<Lad> wiersz(szerokosc + i - 1);
		tl.push_back(wiersz);
	}
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
	tl[2][2].zloze = 'X';

}
void stworzTabliceMiejsc(vector<vector<int>> &tablicaMiejsc)
//funkcja w której do wektora tablicaMiejsc dodajemy odpowiednio długie kolumny
{
	for (int i = 0; i <= wysokosc * 2; i += 2) {
		vector<int> wiersz(szerokosc + i / 2, 7);
		if (i != 0) {

			tablicaMiejsc.push_back(wiersz);
		}
		tablicaMiejsc.push_back(wiersz);
	}
	for (int i = 0; i <= wysokosc * 2 - 2; i += 2) {
		vector<int>wiersz(szerokosc + wysokosc - i / 2 - 1, 7);
		tablicaMiejsc.push_back(wiersz);
		if (i != wysokosc * 2 - 2) {
			tablicaMiejsc.push_back(wiersz);
		}
	}


}

void wstawMiasto(vector<vector<Lad>>&tablicaLadow, vector<vector<int>> &tablicaMiejsc, Player &gracz) {
	unsigned x = 0, y = 0;
	bool poprawnyWybor = false;
	while (poprawnyWybor == 0) {

		cout << endl;
		//cout << "Gracz " << gracz.nr + 1 << " : Postaw miasto:" << endl

		cout << " W którym rzędzie? (możliwe: 0- " << tablicaMiejsc.size() - 1 << ")" << endl;
		x = przyjmijWartosc(0, wysokosc * 4 - 1);

		cout << "Ktore miasto? (możliwe: 0- " << tablicaMiejsc[x].size() - 1 << ")" << endl;

		y = przyjmijWartosc(0, tablicaMiejsc[x].size() - 1);
		poprawnyWybor = dodajLadyGraczowi(tablicaLadow, tablicaMiejsc, gracz, x, y);
		cout << "stan wyboru: " << poprawnyWybor << endl;
	}
	tablicaMiejsc[x][y] = gracz.nr;
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
	time_t t;
	t = clock();
	srand(unsigned(time(&t)));

	int win = 0;
	int PZMax = 0;
	int k1, k2;

	vector<Player> Gracz(iloscGraczy + 1);

	vector<vector<Lad>> tablicaLadow;
	tworzLady(tablicaLadow);

	vector<vector<int>> tablicaMiejsc; //copy
	stworzTabliceMiejsc(tablicaMiejsc); //copy

	//Ustawienie początkowe//

	for (int i = 0; i < iloscGraczy; i++)
	{
		//system("CLS");
		Gracz[i].nr = i;
		narysujPlansze(szerokosc, wysokosc, tablicaMiejsc, tablicaLadow);
		wstawMiasto(tablicaLadow, tablicaMiejsc, Gracz[i]);

	}
	for (int i = iloscGraczy-1; i >=0; i--)
	{
		//system("CLS");
		Gracz[i].nr = i;
		narysujPlansze(szerokosc, wysokosc, tablicaMiejsc, tablicaLadow);
		wstawMiasto(tablicaLadow, tablicaMiejsc, Gracz[i]);

	}


	// kolejka//
	int biezacy = 0;
	do
	{

		int wybor = 0;
		string tablicaWyboru[10] = { "nic","miasto","droga","zamek","rozwoj" };
		int win = 0;
		k1 = rand() % 6 + 1;
		//system("CLS");
		//wypiszTabliceTest(tablicaMiejsc);
		k2 = rand() % 6 + 1;
		narysujPlansze(szerokosc, wysokosc, tablicaMiejsc, tablicaLadow);
		cout <<endl<< "Wynik rzutu: " << k1 << " + " << k2 << " = " << k1 + k2 << endl;
		dajSurowce(Gracz, k1 + k2);
		do {
			cout <<endl<<
				"\t\tGracz: " << Gracz[biezacy].nr + 1 << endl;
			wypiszSurowce(Gracz[biezacy]);
			wypiszMozliwosci(Gracz[biezacy]);

			przyjmijWartosc(wybor, 9);

			switch (wybor) {

			case 1:
				if (sprawdzSurowce(1, Gracz[biezacy])) {
					wstawMiasto(tablicaLadow, tablicaMiejsc, Gracz[biezacy]);
				}
				break;
			case 0:
				++biezacy;
				break;

			}
		} while (wybor!= 0);
		
		if (biezacy >= iloscGraczy) biezacy = 0;
	} while (win == 0);

	return 0;
}
