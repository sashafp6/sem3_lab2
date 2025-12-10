
#ifndef DOUBLY_LINKED_H
#define DOUBLY_LINKED_H

#include <string>

struct NodeD {
    std::string value;
    NodeD* prev; // указатель на предыдущий узел
    NodeD* next; // указатель на следующий узел
};

struct DoublyList {
    NodeD* head; // первый узел
    NodeD* tail; // последний узел
};

DoublyList* createDoublyList();
void pushFrontD(DoublyList* list, const std::string& value);
void pushBackD(DoublyList* list, const std::string& value);
void insertAfterD(DoublyList* list, const std::string& after, const std::string& value);
void insertBeforeD(DoublyList* list, const std::string& before, const std::string& value);
void popFrontD(DoublyList* list);
void popBackD(DoublyList* list);
void removeByValueD(DoublyList* list, const std::string& value);
void removeBeforeD(DoublyList* list, const std::string& key);
void removeAfterD(DoublyList* list, const std::string& key);
NodeD* findD(DoublyList* list, const std::string& value);
void printDoubly(DoublyList* list);
void printDoublyReverse(DoublyList* list);
void loadDoublyFromFile(DoublyList* list, const char* filename);
void saveDoublyToFile(DoublyList* list, const char* filename);
void freeDoubly(DoublyList* list);

#endif
