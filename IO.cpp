#include "pch.h"
#include "IO.h"

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::flush;
using std::endl;


int przyjmijWartosc(int dol, int gora) //funkcja do wymuszenia poprawnej wartosci(jakiegokolwiek inta)
{
	int input;
	do {
		cin >> input;
		if (input < dol || input > gora) {
			cout << "\n Niew³aœciwa wartoœæ, spróbuj ponownie:\n";
		}
		else return input;
	} while (true);
}
inline void rysujMiejsca(int ilosc, int poziom, vector<int>kolumna, string qs = "    ", string ds = "  ")
{
	string wolne;
	for (int i = 0; i < poziom; i++)
	{
		cout << qs << flush;
	}
	for (int i = 0; i < ilosc; i++)
	{
		if (kolumna[i] == 7) wolne = "()";
		if (kolumna[i] == 0) wolne = "M1";
		if (kolumna[i] == 1) wolne = "M2";
		if (kolumna[i] == 2) wolne = "M3";
		if (kolumna[i] == 5) wolne = "||";
		if (kolumna[i] == 9) wolne = "ER";
		cout << wolne << ds << ds << ds << flush;
	}
	cout << endl;
}
inline void rysujMiejsca(int ilosc, int poziom, vector<int>kolumna, vector<Lad>kolumnaLadow, string qs = "    ", string ds = "  ")
{
	string wolne;
	for (int i = 0; i < poziom; i++)
	{
		cout << qs << flush;
	}
	for (int i = 0; i < ilosc; i++)
	{
		string ds2 = "  ";
		if (kolumna[i] == 0) wolne = "()";
		if (kolumna[i] == 1) wolne = "M1";
		if (kolumna[i] == 2) wolne = "M2";
		if (kolumna[i] == 3) wolne = "M3";
		if (kolumna[i] == 5) wolne = "||";
		if (kolumna[i] == 9) wolne = "ER";
		if (i != ilosc - 1) if (kolumnaLadow[i].trigger > 9) ds2 = " ";
		//zeby sie nie przesuwalo gdy trigger ma dwie cyfry

		if (i != ilosc - 1)cout << wolne << ds <<
			kolumnaLadow[i].trigger << kolumnaLadow[i].zloze << ds2 << flush;
		if (i == ilosc - 1)cout << wolne << ds;
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
	cout << endl << ds;


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
	cout << endl << ds;

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
void narysujPlansze(int base, int height, vector<vector<int>> &tablica, vector<vector<Lad>> const &tablicaLadow)
{
	string sl = "//", bs = "\\\\";
	string wolne = "()";
	string ds = "  ";
	string qs = "    ";
	string droga = "||";
	vector<int> tempDroga(10, 5);
	//cout << sl << " " << bs;
	for (int i = 0; i < height; i++) // miasta konczace sie na indeksie nr. 4
	{
		if (i != 0) {
			cout << i * 2 - 1 << " ";
			rysujMiejsca(i + base, height - i, tablica[i * 2 - 1]);
		}
		//if (i != 0) rysujMiejsca(i + base, height - i, tempDroga);
		if (i != 0) {
			cout << "  ";
			rysujMiejsca(i + base, height - i, tempDroga,
				tablicaLadow[i - 1]);

		}
		cout << i * 2 << " ";
		rysujMiejsca(i + base, height - i, tablica[i * 2]);
		cout << "  ";
		DrogiKrzyzowe(i + base, height - i);
	}
	for (int i = height; i >= 0; i--) // od 5. do 12
	{
		cout << height * 4 - i * 2 - 1;
		if (height * 4 - i * 2 - 1 < 10)  cout << " ";
		rysujMiejsca(i + base, height - i, tablica[height * 4 - i * 2 - 1]);
		//if (i != 0)rysujMiejsca(i + base, height - i, tempDroga);
		if (i != 0) {
			cout << ds;
			rysujMiejsca(i + base, height - i, tempDroga,
				tablicaLadow[height * 2 - i - 1]);
		}
		if (i != 0) {
			cout << height * 4 - i * 2;
			if (height * 4 - i * 2 < 10) cout << " ";
			rysujMiejsca(i + base, height - i, tablica[height * 4 - i * 2]);
		}
		if (i != 0) {
			cout << ds;
			DrogiKrzyzoweback(i + base - 1, height - i + 1);
		}
	}


}