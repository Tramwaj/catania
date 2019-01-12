#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "player.h"
#include "lad.h"

using std::vector;
using std::string;

/*struct Lad
{
	int trigger = 0;
	char zloze = 's';
	bool zablokowany;
};

struct Player
{
	int nr;
	vector<Lad> Lady;
	unsigned kamien;
	unsigned drewno;
	unsigned owce;
	unsigned zboze;
	unsigned cegly;

};*/

int przyjmijWartosc(int dol, int gora);
inline void rysujMiejsca(int ilosc, int poziom, vector<int>kolumna, string qs, string ds);
inline void rysujMiejsca(int ilosc, int poziom, vector<int>kolumna, vector<Lad>kolumnaLadow, string q, string ds);
inline void DrogiKrzyzowe(int ilosc, int poziom, string sl, string bs, string qs, string ds);
inline void DrogiKrzyzoweback(int ilosc, int poziom, string sl, string bs, string qs, string ds);
void narysujPlansze(int base, int height, vector<vector<int>> &tablica, vector<vector<Lad>> const &tablicaLadow);