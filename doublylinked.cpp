#include "doublylinked.h"
#include <iostream>
#include <fstream>

// Создание пустого списка
DoublyList* createDoublyList() {
    DoublyList* list = new DoublyList;
    list->head = nullptr; // список пустой
    list->tail = nullptr;
    return list;
}

// добавление в начало
void pushFrontD(DoublyList* list, const std::string& value) {
    NodeD* node = new NodeD;
    node->value = value;
    node->prev = nullptr; // новый становится первым
    node->next = list->head; // нет хвоста

    if (list->head) list->head->prev = node; // если список пуст, у старой головы новый предыдущ элемент
    list->head = node;
    if (!list->tail) list->tail = node; 
}

// добавление в конец в конец
void pushBackD(DoublyList* list, const std::string& value) {
    NodeD* node = new NodeD;
    node->value = value;
    node->next = nullptr;
    node->prev = list->tail;

    if (list->tail) list->tail->next = node; // если был хвост, свыязываем с новым
    list->tail = node;
    if (!list->head) list->head = node;
}

// Вставить после элемента
void insertAfterD(DoublyList* list, const std::string& after, const std::string& value) {
    NodeD* current = list->head;
    while (current && current->value != after) // поиск узла с заданным значением
        current = current->next;
    if (!current) return;

    NodeD* node = new NodeD;
    node->value = value;
    node->next = current->next; // связываем со след и с предыдущим
    node->prev = current;

    if (current->next) current->next->prev = node; //если есть следующий, то обновляем
    current->next = node;
    if (list->tail == current) list->tail = node;
}

// вставка перед элементом
void insertBeforeD(DoublyList* list, const std::string& before, const std::string& value) {
    NodeD* current = list->head;
    while (current && current->value != before) // поиск элемента, перед которым будем вставлять
        current = current->next;
    if (!current) return;

    NodeD* node = new NodeD;
    node->value = value;
    node->prev = current->prev;
    node->next = current;

    if (current->prev) current->prev->next = node; // переназначаем, если был был предыдущий
    current->prev = node;
    if (list->head == current) list->head = node;
}

// удаление из начала
void popFrontD(DoublyList* list) {
    if (!list->head) return;
    NodeD* temp = list->head; // сохраняем голову
    list->head = list->head->next; // новая голова - след элемент
    if (list->head) list->head->prev = nullptr;
    else list->tail = nullptr; // если список пустой - хвоста больше нет
    delete temp;
}

// удаление из конца
void popBackD(DoublyList* list) {
    if (!list->tail) return;
    NodeD* temp = list->tail; // сохраняем старый хвост
    list->tail = list->tail->prev;  // новый хвост предыдущий элемент
    if (list->tail) list->tail->next = nullptr;
    else list->head = nullptr;
    delete temp;
}

// удаление по значению
void removeByValueD(DoublyList* list, const std::string& value) {
    NodeD* current = list->head;
    while (current) { //проходим по всем узлам
        if (current->value == value) { 
            NodeD* temp = current;
            if (current->prev) current->prev->next = current->next; // переназначаем ссылки соседей
            else list->head = current->next; // если удаляем голову
            if (current->next) current->next->prev = current->prev;
            else list->tail = current->prev; // если удаляем хвост
            current = current->next;
            delete temp; 
        } else {
            current = current->next;
        }
    }
}

// Удаление элемента после заданного значения
void removeAfterD(DoublyList* list, const std::string& value) {
    if (!list->head) return;

    NodeD* current = list->head;
    while (current && current->value != value)
        current = current->next;

    if (!current || !current->next) return; // нет элемента после

    NodeD* temp = current->next;
    current->next = temp->next;
    if (temp->next)
    temp->next->prev = current;
    else
        list->tail = current; // если удалили хвост

    delete temp;
}

// Удаление элемента перед заданным значением
void removeBeforeD(DoublyList* list, const std::string& value) {
    if (!list->head || list->head->value == value) return; // нет элемента перед первым

    NodeD* current = list->head;
    while (current && current->value != value)
        current = current->next;

    if (!current || !current->prev) return; // нет элемента перед

    NodeD* temp = current->prev;
    if (temp->prev)
        temp->prev->next = current;
    else
        list->head = current; // если удалили голову
    current->prev = temp->prev;

    delete temp;
}

// Найти по значению
NodeD* findD(DoublyList* list, const std::string& value) {
    NodeD* current = list->head;
    while (current) {
        if (current->value == value) return current;
        current = current->next;
    }
    return nullptr;
}

// Печать списка
void printDoubly(DoublyList* list) {
    NodeD* current = list->head;
    while (current) {
        std::cout << current->value;
        if (current->next) std::cout << " <-> ";
        current = current->next;
    }
    std::cout << std::endl;
}

void printDoublyReverse(DoublyList* list){
    NodeD* current = list -> tail;
    if (!current){
        std::cout << "Список пуст. \n";
        return;
    }
    while(current){
        std::cout << current->value;
        if (current->prev) std::cout<< "<->";
        current = current->prev;
    }
    std::cout << " -> nullptr\n";
}

// Загрузка из текстового файла (построчно)
void loadDoublyFromFile(DoublyList* list, const char* filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(fin, line)) {
        if (!line.empty())
            pushBackD(list, line);
    }

    fin.close();
}

// Сохранение в текстовый файл
void saveDoublyToFile(DoublyList* list, const char* filename) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }

    NodeD* current = list->head;
    while (current) {
        fout << current->value << "\n";
        current = current->next;
    }

    fout.close();
}

// Очистка списка
void freeDoubly(DoublyList* list) {
    while (list->head)
        popFrontD(list);
    delete list;
}
