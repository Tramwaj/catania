#include "pch.h"
#include "player.h"

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;

bool dodajLadyGraczowi(vector<vector<Lad>> &tablicaLadow, vector<vector<int>> &tablicaMiejsc, Player &gracz, unsigned m, unsigned n) {
	unsigned m1 = m / 2 - 1;
	unsigned m2 = m / 2;
	if (tablicaMiejsc[m][n] != 7) {
		cout << " To pole jest ju¿ zajête. Wybierz inne. " << endl;
		return 0;
	}
	if (m < tablicaMiejsc.size() / 2) { //pierwsza po³owa
		if (m % 2 == 0) { //parzyste
			if (m > 0 && n > 0) {
				gracz.Lady.push_back(tablicaLadow[m1][n - 1]);
			}
			if (m > 0 && n < tablicaMiejsc[m].size() - 1) {
				gracz.Lady.push_back(tablicaLadow[m1][n]);
			}
			gracz.Lady.push_back(tablicaLadow[m2][n]);

		}
		else { //nieparzyste
			if ((m > 1) && (n > 0) && n < tablicaMiejsc[m].size() - 1) {
				gracz.Lady.push_back(tablicaLadow[m1][n - 1]);
			}
			if (n > 0) {
				gracz.Lady.push_back(tablicaLadow[m2][n - 1]);
			}
			if (n < tablicaMiejsc[m].size() - 1) {
				gracz.Lady.push_back(tablicaLadow[m2][n]);
			}
		}

	}
	else { // druga po³owa
		if (m % 2 == 0) { //parzyste
			if (n > 0) {
				gracz.Lady.push_back(tablicaLadow[m1][n - 1]);
			}
			if (n < tablicaMiejsc[m].size() - 1) {
				gracz.Lady.push_back(tablicaLadow[m1][n]);
			}
			if (n > 0 && n < tablicaMiejsc[m].size() - 1 && m <
				tablicaMiejsc.size() - 2) {
				gracz.Lady.push_back(tablicaLadow[m2][n - 1]);
			}
		}
		else { //nieparzyste

			gracz.Lady.push_back(tablicaLadow[m1][n]);

			if (n > 0 && m < tablicaMiejsc.size() - 1) {
				gracz.Lady.push_back(tablicaLadow[m2][n - 1]);
			}
			if (n < tablicaMiejsc[m].size() - 1 && m <
				tablicaMiejsc.size() - 1) {
				gracz.Lady.push_back(tablicaLadow[m2][n]);
			}
		}
	}


	return true;
}
void dajSurowce(vector<Player> &Gracz, const unsigned wynik)
{
	for (auto &biezacyGracz : Gracz)
		for (auto biezacyLad : biezacyGracz.Lady)
			if (biezacyLad.trigger == wynik) {
				switch (biezacyLad.zloze) {
				case 'K':
					biezacyGracz.kamien++;
					cout << "Gracz nr. " << biezacyGracz.nr + 1 << " otrzymuje kamieñ! \t";
					break;
				case 'D':
					biezacyGracz.drewno++;
					cout << "Gracz nr. " << biezacyGracz.nr + 1 << " otrzymuje drewno! \t";
					break;
				case 'O':
					biezacyGracz.owce++;
					cout << "Gracz nr. " << biezacyGracz.nr + 1 << " otrzymuje owce! \t";
					break;
				case 'Z':
					biezacyGracz.zboze++;
					cout << "Gracz nr. " << biezacyGracz.nr + 1 << " otrzymuje zbo¿e! \t";
					break;
				case 'C':
					biezacyGracz.cegly++;
					cout << "Gracz nr. " << biezacyGracz.nr + 1 << " otrzymuje ceg³y! \t";
					break;
				}
				cout << endl;
			}

}
void wypiszSurowce(const Player Gracz)
{
	cout << "Kamieñ: " << Gracz.kamien << endl;
	cout << "Drewno: " << Gracz.drewno << endl;
	cout << "Owce: " << Gracz.owce << endl;
	cout << "Zbo¿e: " << Gracz.zboze << endl;
	cout << "Ceg³y: " << Gracz.cegly << endl;
}
bool sprawdzSurowce(const int wybor, const Player Gracz)
{
	unsigned cegly = 0;
	unsigned kamien = 0;
	unsigned drewno = 0;
	unsigned owce = 0;
	unsigned zboze = 0;

	switch (wybor) {
	case 1:
		cegly = 1;
		drewno = 1;
		owce = 1;
		zboze = 1;
		break;
	case 3:
		kamien = 3;
		zboze = 2;
		break;
	case 2:
		cegly = 1;
		drewno = 1;
		break;
	case 4:
		kamien = 1;
		owce = 1;
		zboze = 1;
		break;
	}
	if (kamien > Gracz.kamien || cegly > Gracz.cegly || drewno > Gracz.cegly || owce > Gracz.owce || zboze > Gracz.zboze) {
		return 0;
	}
	else return 1;
}
void wypiszMozliwosci(const Player Gracz)
{
	cout << "Co chcesz zrobiæ?" << endl;
	if (sprawdzSurowce(1, Gracz)) {
		cout << "1 - miasto" << endl;
	}
	if (sprawdzSurowce(2, Gracz)) {
		cout << "2 - droga" << endl;
	}
	if (sprawdzSurowce(3, Gracz)) {
		cout << "3 - miasto" << endl;
	}
	if (sprawdzSurowce(4, Gracz)) {
		cout << "4 - rozwoj" << endl;
	}
	else {
		cout << "Jesteœ biedny i nic nie mo¿esz z tym zrobiæ." << endl;
	}
	cout << "0 - koniec tury" << endl;
}