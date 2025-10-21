#include <iostream>
using namespace std;

// Klasa wezla listy
template<typename T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(T value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

// Iterator listy
template<typename T>
class ListIterator {
    Node<T>* current;
public:
    ListIterator(Node<T>* node) : current(node) {}

    bool hasNext() { return current && current->next; }
    bool hasPrev() { return current && current->prev; }

    void next() { if (hasNext()) current = current->next; }
    void prev() { if (hasPrev()) current = current->prev; }

    T get() { return current->data; }
};

// Klasa listy dwukierunkowej
template<typename T>
class DoublyLinkedList {
    Node<T>* head;
    Node<T>* tail;
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    };

    // Dodaj element na poczatek listy
    void push_front(T value) {
        Node<T>* node = new Node<T>(value);
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
    }
    // Dodaj element na koniec listy
    void push_back(T value) {
        Node<T>* node = new Node<T>(value);
        node->prev = tail;
        if (tail) tail->next = node;
        tail = node;
        if (!head) head = node;
    }
    // Wyświetl całą listę
    void print() {
        Node<T>* temp = head;
        cout << "Lista: ";
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Zwróć iterator na początek listy
    ListIterator<T> begin() { return ListIterator<T>(head); }
};

// Wzorzec Factory
template<typename T>
class ListFactory {
public:
    static DoublyLinkedList<T>* create() {
        return new DoublyLinkedList<T>();
    }
};


int main() {
    
}
