#include "lista.h"
#include <iostream>
#include "powiazanie.cpp"

using namespace std;

/**
 * @brief Domyślny konstruktor klasy ListaDwuKierunkowa.
 *
 * Inicjalizuje nową, pustą listę. Ustawia wskaźniki 'przod' (głowa) i 'tyl' (ogon)
 * na 'nullptr', co sygnalizuje, że lista nie zawiera jeszcze żadnych elementów.
 */
ListaDwuKierunkowa::ListaDwuKierunkowa() {
    przod = nullptr;
    tyl = nullptr;
}

/**
 * @brief Wyświetla zawartość listy w kolejności od początku do końca.
 *
 * Tworzy tymczasowy wskaźnik 'aktualny', który zaczyna od 'przod'.
 * Najpierw sprawdza, czy lista jest pusta (czy 'przod' to 'nullptr').
 * Jeśli tak, wyświetla stosowny komunikat i kończy działanie.
 * W przeciwnym razie, iteruje przez listę w pętli 'while', dopóki 'aktualny'
 * nie osiągnie 'nullptr' (końca listy). W każdej iteracji wypisuje
 * wartość 'dane' bieżącego węzła i przesuwa wskaźnik na następny element.
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
 * @brief Wyświetla zawartość listy w kolejności od końca do początku.
 *
 * Działa analogicznie do metody 'wyswietl()', ale rozpoczyna iterację
 * od wskaźnika 'tyl' (ogon listy).
 * W pętli 'while' przesuwa się wstecz, używając wskaźnika 'poprzedni',
 * aż do osiągnięcia 'nullptr' (początku listy).
 */
void ListaDwuKierunkowa::wyswietlNaOdwrot() {
    Powiazanie* aktualny = tyl;
    // Sprawdzenie, czy lista nie jest pusta
    if (!przod) {
        cout << "Lista jest pusta." << endl;
        return;
    }
    // Pętla iterująca od początku do końca
    while (aktualny) {
        cout << aktualny->dane << " ";
        aktualny = aktualny->poprzedni;// Przesunięcie do kolejnego węzła
    }
    cout << endl;// Zakończenie linii po wyświetleniu wszystkich elementów
}
/**
 * @brief Dodaje nowy element na sam początek (przód) listy.
 *
 * @param x Wartość (liczba całkowita), która ma być przechowywana w nowym węźle.
 *
 * Alokuje pamięć dla nowego węzła 'Powiazanie'.
 * 1. Jeśli lista jest pusta (!przod), nowy węzeł staje się jednocześnie
 * początkiem ('przod') i końcem ('tyl') listy.
 * 2. Jeśli lista nie jest pusta, nowy węzeł jest "wpinany" przed stary 'przod':
 * - 'nowe->nastepny' wskazuje na dotychczasowy 'przod'.
 * - 'przod->poprzedni' (wskaźnik zwrotny starej głowy) wskazuje na 'nowe'.
 * - Globalny wskaźnik 'przod' jest aktualizowany, by wskazywał na 'nowe'.
 */
void ListaDwuKierunkowa::dodajNaPrzod(int x) {
    Powiazanie* nowe = new Powiazanie(x);
    // Sprawdzenie, czy lista nie jest pusta
    if (!przod) { // Wystarczy sprawdzić 'przod', 'tyl' też będzie nullptr
        przod = tyl = nowe;
    }
    else {
        nowe->nastepny = przod;
        przod->poprzedni = nowe;
        przod = nowe;
    }
}

/**
 * @brief Dodaje nowy element na sam koniec (tył) listy.
 *
 * @param x Wartość (liczba całkowita), która ma być przechowywana w nowym węźle.
 *
 * Działa analogicznie do 'dodajNaPrzod', ale operuje na wskaźniku 'tyl'.
 * 1. Jeśli lista jest pusta (!tyl), nowy węzeł staje się 'przodem' i 'tylem'.
 * 2. Jeśli lista nie jest pusta, nowy węzeł jest "dopinany" za stary 'tyl':
 * - 'tyl->nastepny' (wskaźnik do przodu starego ogona) wskazuje na 'nowe'.
 * - 'nowe->poprzedni' wskazuje na dotychczasowy 'tyl'.
 * - Globalny wskaźnik 'tyl' jest aktualizowany, by wskazywał na 'nowe'.
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
 * @brief Usuwa pierwszy element (węzeł 'przod') z listy.
 *
 * Jeśli lista jest pusta ('!przod'), funkcja nic nie robi.
 * W przeciwnym razie, przechowuje wskaźnik do usuwanego węzła w 'temp'.
 * 1. Przypadek specjalny: lista ma tylko jeden element ('przod == tyl').
 * Po usunięciu lista staje się pusta, więc 'przod' i 'tyl' są ustawiane na 'nullptr'.
 * 2. Przypadek standardowy: lista ma więcej elementów.
 * - Wskaźnik 'przod' jest przesuwany na następny element ('przod->nastepny').
 * - Nowy 'przod' musi mieć wskaźnik 'poprzedni' ustawiony na 'nullptr',
 * ponieważ staje się pierwszym elementem (odcinamy połączenie ze starym 'przodem').
 * Na końcu pamięć wskazywana przez 'temp' jest zwalniana.
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
 * @brief Usuwa ostatni element (węzeł 'tyl') z listy.
 *
 * Działa symetrycznie do 'usunPrzod'.
 * Jeśli lista jest pusta ('!tyl'), funkcja nic nie robi.
 * Przechowuje wskaźnik do 'tyl' w 'temp'.
 * 1. Przypadek specjalny: jeden element ('przod == tyl'). Lista staje się pusta.
 * 2. Przypadek standardowy: więcej elementów.
 * - Wskaźnik 'tyl' jest przesuwany na poprzedni element ('tyl->poprzedni').
 * - Nowy 'tyl' musi mieć wskaźnik 'nastepny' ustawiony na 'nullptr',
 * ponieważ staje się ostatnim elementem.
 * Na końcu pamięć wskazywana przez 'temp' jest zwalniana.
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
 * @brief Dodaje nowy element o wartości 'val' na pozycję określoną przez 'index'.
 *
 * @param val Wartość do wstawienia.
 * @param index Pozycja, na którą element ma być wstawiony (licząc od 0).
 *
 * 1. Jeśli 'index' to 0, wywoływana jest funkcja 'dodajNaPrzod'.
 * 2. W przeciwnym razie, funkcja iteruje przez listę do węzła na pozycji 'index - 1'
 * (czyli węzła *przed* miejscem docelowym).
 * 3. Jeśli 'index' jest poza zakresem (np. 10 na 5-elementowej liście),
 * pętla zakończy się, a warunek '(!aktualny || !aktualny->nastepny)'
 * sprawi, że element zostanie dodany na końcu listy przez 'dodajNaTyl'.
 * 4. Jeśli 'index' jest w środku listy, tworzony jest nowy węzeł i "wpinany"
 * pomiędzy 'aktualny' (na poz. index-1) a 'aktualny->nastepny' (na poz. index).
 * Wymaga to aktualizacji 4 wskaźników.
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
 *
 * @param index Indeks elementu do usunięcia (licząc od 0).
 *
 * 1. Jeśli 'index' to 0, wywoływana jest funkcja 'usunPrzod'.
 * 2. W przeciwnym razie, funkcja iteruje do węzła *na* pozycji 'index'.
 * 3. Jeśli 'index' jest poza zakresem, wyświetlany jest błąd.
 * 4. Jeśli węzeł na pozycji 'index' jest ostatnim elementem ('aktualny == tyl'),
 * wywoływana jest funkcja 'usunTyl'.
 *
 * 5. Jeśli element jest w środku listy, kod wykonuje tylko 'delete aktualny'.
 * NIE następuje połączenie węzła 'aktualny->poprzedni' z 'aktualny->nastepny'.
 * To powoduje uszkodzenie struktury listy i prowadzi do awarii programu.
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
 * @brief Wyświetla wartość elementu następującego po węźle o podanym indeksie.
 *
 * @param index Indeks węzła, którego następnika szukamy.
 *
 * Funkcja najpierw iteruje do węzła na pozycji 'index'.
 * Jeśli węzeł ten ('aktualny') istnieje i ma następnika ('aktualny->nastepny'),
 * wyświetla jego wartość.
 * W przeciwnym razie (indeks zły lub brak następnika), wyświetla komunikat.
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
 * @brief Wyświetla wartość elementu poprzedzającego węzeł o podanym indeksie.
 *
 * @param index Indeks węzła, którego poprzednika szukamy.
 *
 * Działa analogicznie do 'wyswietlNastepny'.
 * Iteruje do węzła na pozycji 'index'.
 * Jeśli węzeł ten ('aktualny') istnieje i ma poprzednika ('aktualny->poprzedni'),
 * wyświetla jego wartość.
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
 * @brief Usuwa wszystkie elementy z listy i zwalnia zajmowaną przez nie pamięć.
 *
 * Funkcja działa w pętli, dopóki wskaźnik 'przod' nie stanie się 'nullptr'.
 * W każdej iteracji wywołuje 'usunPrzod()', która bezpiecznie usuwa
 * pierwszy element i przesuwa wskaźnik 'przod'. Jest to efektywny
 * i bezpieczny sposób na opróżnienie listy.
 */
void ListaDwuKierunkowa::wyczysc() {
    while (przod) {
        usunPrzod();
    }
}

/**
 * @brief Funkcja testowa, która tworzy "na sztywno" dwuelementową listę.
 * Funkcja ta tworzy dwa nowe węzły i bezwarunkowo nadpisuje
 * globalne wskaźniki 'przod' i 'tyl'.
 * Jeśli lista zawierała wcześniej jakieś elementy, wskaźniki do nich
 * zostają utracone, a pamięć po nich nigdy nie będzie zwolniona,
 * co prowadzi do wycieku pamięci.
 * Poprawna implementacja powinna najpierw wywołać 'wyczysc()'.
 */
void ListaDwuKierunkowa::test() {
    Powiazanie* pierwszy = new Powiazanie(2);
    Powiazanie* drugi = new Powiazanie(6);

    pierwszy->nastepny = drugi;
    drugi->poprzedni = pierwszy;

    przod = pierwszy;
    tyl = drugi;
}
