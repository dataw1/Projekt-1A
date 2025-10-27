#pragma once

/**
 * @brief Struktura reprezentuj�ca powi�zanie w li�cie dwukierunkowej
 */

struct Powiazanie {
	int dane;
	Powiazanie* nastepny;
	Powiazanie* poprzedni;

	Powiazanie(int wartosc) : dane(wartosc), nastepny(nullptr), poprzedni(nullptr) {}
};