#include "lista.h"
#include <iostream>
#include "powiazanie.cpp"

using namespace std;

/**
 * @brief Konstruktor inicjalizujący pustą listę dwukierunkową.
 * Ustawia wskaźniki przod i tyl na nullptr, co oznacza brak elementów początkowych.
 */
ListaDwuKierunkowa::ListaDwuKierunkowa() {
    przod = nullptr;
    tyl = nullptr;
}

/**
 * @brief Wyświetla elementy listy od początku do końca.
 * Iteruje po kolejnych węzłach i wypisuje przechowywane wartości.
 * Jeżeli lista jest pusta, informuje o braku elementów.
 */
void ListaDwuKierunkowa::wyswietl() {
    Powiazanie* aktualny = przod;

    if (!przod) {
        cout << "Lista jest pusta." << endl;
        return;
    }

    while (aktualny) {
        cout << aktualny->dane << " ";
        aktualny = aktualny->nastepny;
    }
    cout << endl;
}

/**
 * @brief Wyświetla elementy listy od końca do początku.
 * Iteruje od węzła tyl do przodu, wypisując wartości w odwrotnej kolejności.
 * Jeżeli lista jest pusta, informuje o braku elementów.
 */
void ListaDwuKierunkowa::wyswietlNaOdwrot() {
    Powiazanie* aktualny = tyl;

    if (!przod) {
        cout << "Lista jest pusta." << endl;
        return;
    }

    while (aktualny) {
        cout << aktualny->dane << " ";
        aktualny = aktualny->poprzedni;
    }
    cout << endl;
}

/**
 * @brief Dodaje nowy element na początek listy.
 * Tworzy węzeł Powiazanie i dołącza go przed dotychczasowym przodem listy.
 * Jeżeli lista była pusta, nowy element staje się jednocześnie przodem i tyłem.
 * @param x Wartość przypisana do nowego elementu.
 */
void ListaDwuKierunkowa::dodajNaPrzod(int x) {
    Powiazanie* nowe = new Powiazanie(x);
    if (!przod) {
        przod = tyl = nowe;
    }
    else {
        nowe->nastepny = przod;
        przod->poprzedni = nowe;
        przod = nowe;
    }
}

/**
 * @brief Dodaje nowy element na koniec listy.
 * Tworzy węzeł Powiazanie i dołącza go za dotychczasowym tyłem listy.
 * Jeżeli lista była pusta, nowy element pełni rolę przodu oraz tyłu.
 * @param x Wartość przypisana do nowego elementu.
 */
void ListaDwuKierunkowa::dodajNaTyl(int x) {
    Powiazanie* nowe = new Powiazanie(x);
    if (!tyl) {
        przod = tyl = nowe;
    }
    else {
        tyl->nastepny = nowe;
        nowe->poprzedni = tyl;
        tyl = nowe;
    }
}

/**
 * @brief Usuwa element na początku listy.
 * Zwalnia pierwszy węzeł i aktualizuje wskaźnik przod.
 * Gdy po operacji lista jest pusta, zeruje również wskaźnik tyl.
 */
void ListaDwuKierunkowa::usunPrzod() {
    if (!przod) return;

    Powiazanie* temp = przod;
    if (przod == tyl) {
        przod = tyl = nullptr;
    }
    else {
        przod = przod->nastepny;
        if (przod) {
            przod->poprzedni = nullptr;
        }
    }
    delete temp;
}

/**
 * @brief Usuwa element na końcu listy.
 * Zwalnia ostatni węzeł i aktualizuje wskaźnik tyl.
 * Jeżeli po usunięciu lista jest pusta, zeruje także wskaźnik przod.
 */
void ListaDwuKierunkowa::usunTyl() {
    if (!tyl) return;

    Powiazanie* temp = tyl;
    if (przod == tyl) {
        przod = tyl = nullptr;
    }
    else {
        tyl = tyl->poprzedni;
        if (tyl) {
            tyl->nastepny = nullptr;
        }
    }
    delete temp;
}

/**
 * @brief Dodaje nowy element pod wskazanym indeksem listy.
 * Dla indeksu równego zero wstawia węzeł na początek, a gdy pozycja wykracza poza listę dołącza element na końcu.
 * @param val Wartość przypisana do nowego elementu.
 * @param index Indeks, pod którym należy umieścić nowy węzeł.
 */
void ListaDwuKierunkowa::dodajPodIndeks(int val, int index) {
    if (index == 0) {
        dodajNaPrzod(val);
        return;
    }

    Powiazanie* aktualny = przod;
    for (int i = 0; i < index - 1; ++i) {
        if (!aktualny) {
            cout << "Indeks " << index << " nie istnieje." << endl;
            return;
        }
        aktualny = aktualny->nastepny;
    }

    if (!aktualny || !aktualny->nastepny) {
        dodajNaTyl(val);
        return;
    }

    Powiazanie* nowe = new Powiazanie(val);
    nowe->nastepny = aktualny->nastepny;
    nowe->poprzedni = aktualny;
    aktualny->nastepny->poprzedni = nowe;
    aktualny->nastepny = nowe;
}

/**
 * @brief Usuwa element znajdujący się pod danym indeksem.
 * Dla indeksu równego zero usuwa pierwszy element; brak wskazanego węzła sygnalizuje komunikatem o błędzie.
 * @param index Indeks elementu przeznaczonego do usunięcia.
 */
void ListaDwuKierunkowa::usunIndeks(int index) {
    if (index == 0) {
        usunPrzod();
        return;
    }

    Powiazanie* aktualny = przod;
    for (int i = 0; i < index; ++i) {
        if (!aktualny->nastepny) {
            cout << "Indeks " << index << " nie istnieje." << endl;
            return;
        }
        aktualny = aktualny->nastepny;
    }

    if (!aktualny) {
        cout << "Indeks " << index << " nie istnieje." << endl;
        return;
    }

    if (aktualny == tyl) {
        usunTyl();
        return;
    }

    delete aktualny;
}

/**
 * @brief Wyświetla element następujący po węźle o podanym indeksie.
 * Gdy istnieje kolejny element, wypisuje jego wartość, w przeciwnym razie informuje o braku następnika.
 * @param index Indeks elementu, dla którego sprawdzany jest następnik.
 */
void ListaDwuKierunkowa::wyswietlNastepny(int index) {
    Powiazanie* aktualny = przod;

    for (int i = 0; i < index; ++i)
    {
        if (!aktualny) {
            cout << "Indeks " << index << " nie istnieje." << endl;
            return;
        }
        aktualny = aktualny->nastepny;
    }

    if (aktualny && aktualny->nastepny)
    {
        cout << "Nastepny element dla indeksu " << index << ": " << aktualny->nastepny->dane << endl;
    }
    else {
        cout << "Brak nastepnego elementu dla indeksu " << index << "." << endl;
    }
}

/**
 * @brief Wyświetla element poprzedzający węzeł o podanym indeksie.
 * Gdy istnieje poprzednik, wypisuje jego wartość, a w przeciwnym wypadku informuje o jej braku.
 * @param index Indeks elementu, dla którego sprawdzany jest poprzednik.
 */
void ListaDwuKierunkowa::wyswietlPoprzedni(int index) {
    Powiazanie* aktualny = przod;

    for (int i = 0; i < index; ++i)
    {
        if (!aktualny) {
            cout << "Indeks " << index << " nie istnieje." << endl;
            return;
        }
        aktualny = aktualny->nastepny;
    }

    if (aktualny && aktualny->poprzedni)
    {
        cout << "Poprzedni element dla indeksu " << index << ": " << aktualny->poprzedni->dane << endl;
    }
    else {
        cout << "Brak poprzedniego elementu dla indeksu " << index << "." << endl;
    }
}

/**
 * @brief Usuwa wszystkie elementy z listy.
 * Iteracyjnie zwalnia węzły rozpoczynając od przodu, aż struktura będzie pusta.
 */
void ListaDwuKierunkowa::wyczysc() {
    while (przod) {
        usunPrzod();
    }
}

/**
 * @brief Testowo tworzy dwuelementowy układ połączeń.
 * Dodaje dwa węzły, łączy je ze sobą i przypisuje jako przód oraz tył listy.
 */
void ListaDwuKierunkowa::test() {
    Powiazanie* pierwszy = new Powiazanie(2);
    Powiazanie* drugi = new Powiazanie(6);

    pierwszy->nastepny = drugi;
    drugi->poprzedni = pierwszy;

    przod = pierwszy;
    tyl = drugi;
}
