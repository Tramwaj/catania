#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "lad.h"

using std::vector;

struct Player
{
	int nr;
	vector<Lad> Lady;
	unsigned kamien;
	unsigned drewno;
	unsigned owce;
	unsigned zboze;
	unsigned cegly;

};

bool dodajLadyGraczowi(vector<vector<Lad>> &tablicaLadow, vector<vector<int>> &tablicaMiejsc, Player &gracz, unsigned m, unsigned n);
void dajSurowce(vector<Player> &Gracz, const unsigned wynik);
void wypiszSurowce(const Player Gracz);
bool sprawdzSurowce(const int wybor, const Player Gracz);
void wypiszMozliwosci(const Player Gracz);
