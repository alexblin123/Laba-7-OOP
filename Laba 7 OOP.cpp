#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>

class Pair {

public:

    T first, second;

    Pair(T f = 0, T s = 0) {
        first = f;
        second = s;
    }

    friend ostream& operator<<(ostream& os, const Pair& pair) {
        os << pair.first << " : " << pair.second;
        return os;
    }
};

template <typename T>

struct Node {

    T data;
    Node<T>* next_node;
    Node<T>* prev_node;
};

template <typename T>

class List {

private:

    int size;
    Node<T>* head;
    Node<T>* tail;

public:

    List() {
        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    List(int size, T data) {

        this->size = size;

        if (size > 0) {

            Node<T>* node = new Node<T>;
            node->data = data;
            this->head = node;
            this->tail = node;

            for (int i = 1; i < size; i++) {

                Node<T>* newNode = new Node<T>;
                newNode->data = data;
                tail->next_node = newNode;
                newNode->prev_node = tail;
                tail = newNode;
            }
            tail->next_node = nullptr;
        }
        else {
            this->head = nullptr;
            this->tail = nullptr;
        }
    }

    List(const List& list) {

        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;

        Node<T>* current_node = list.head;
        while (current_node != nullptr) {
            push_back(current_node->data);
            current_node = current_node->next_node;
        }
    }

    ~List() {

        Node<T>* current_node = head;
        while (current_node != nullptr) {
            Node<T>* next_node = current_node->next_node;
            delete current_node;
            current_node = next_node;
        }
        head = nullptr;
    }

    T front() const { return this->head->data; }

    T back() const { return this->tail->data; }

    void push_back(T data) {

        Node<T>* new_node = new Node<T>;
        new_node->data = data;
        new_node->next_node = nullptr;

        if (this->head == nullptr) {
            this->head = new_node;
            this->tail = new_node;
        }
        else {
            tail->next_node = new_node;
            new_node->prev_node = tail;
            tail = new_node;
        }
        this->size++;
    }

    bool is_empty() const { return this->size == 0; }

    int operator () () const { return this->size; }

    T& operator [] (int index) {

        Node<T>* current_node = this->head;
        for (int i = 0; i < index; i++) {
            current_node = current_node->next_node;
        }
        return current_node->data;
    }

    const T& operator [] (int index) const {

        Node<T>* current_node = this->head;
        for (int i = 0; i < index; i++) {
            current_node = current_node->next_node;
        }
        return current_node->data;
    }

    List<T> operator* (const List<T>& other) const {

        int min_size = min(this->size, other.size);
        List<T> result;
        for (int i = 0; i < min_size; ++i) {
            result.push_back(this->operator[](i) * other[i]);
        }
        return result;
    }

    friend ostream& operator<<(ostream& out, const List& list) {

        out << "\nВывод элементов списка\n";

        Node<T>* current_node = list.head;
        while (current_node != nullptr) {
            out << current_node->data << " ";
            current_node = current_node->next_node;
        }
        out << "\nВывод элементов завершён\n";
        return out;
    }
};

int main() {

    system("chcp 1251 > Null");

    Pair<int> pair(12.6578, 20.515);
    cout << "Пара чисел (типа int): " << pair << endl;

    Pair<double> pair2(12.144, 20.515);
    cout << "Пара чисел (типа double): " << pair2 << endl;

    List<double> firstList(10, 0);

    cout << "\nВведите 10 чисел первого списка (типа double)\n";
    for (int i = 0; i < firstList(); i++) {
        cout << i + 1 << ": ";
        cin >> firstList[i];
    }

    cout << firstList;

    List<double> secondList(10, 0);

    cout << "\nВведите 10 чисел второго списка (типа double)\n";
    for (int i = 0; i < secondList(); i++) {
        cout << i + 1 << ": ";
        cin >> secondList[i];
    }

    cout << secondList;

    cout << "\nПервый элемент первого списка: " << firstList.front() << endl;
    cout << "\nПоследний элемент второго списка: " << secondList.back() << endl;

    List<double> listThree = firstList * secondList;

    cout << "\nПеремноженные соответсвующие элементы первого и второго списков\n";
    cout << listThree;

    return 0;
}
