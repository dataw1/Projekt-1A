#pragma once

/**
 * @brief Struktura reprezentuj¹ca powi¹zanie w liœcie dwukierunkowej
 */

struct Powiazanie {
	int dane;
	Powiazanie* nastepny;
	Powiazanie* poprzedni;

	Powiazanie(int wartosc) : dane(wartosc), nastepny(nullptr), poprzedni(nullptr) {}
};