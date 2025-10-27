#include <iostream>
#include <conio.h>
#include "lista.h"

using namespace std;

int main() {
	ListaDwuKierunkowa lista;

	lista.test();

	lista.wyswietl();

	lista.wyswietlNaOdwrot();

	lista.dodajNaPrzod(10);

	lista.wyswietl();

	lista.dodajNaTyl(103);

	lista.wyswietl();

	lista.usunPrzod();

	lista.wyswietl();

	lista.usunTyl();

	lista.wyswietl();

	lista.wyczysc();

	lista.wyswietl();

	lista.test();

	lista.dodajPodIndeks(1, 0);

	lista.wyswietl();

	lista.usunIndeks(2);

	lista.wyswietl();

	lista.dodajPodIndeks(7, 0);

	lista.wyswietlNastepny(1);

	lista.wyswietlPoprzedni(1);

	lista.wyswietlNastepny(2);

	lista.wyswietlPoprzedni(2);

	lista.wyswietl();

	return 0;
}
