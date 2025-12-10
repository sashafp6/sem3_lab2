#include "stack.h"
#include <iostream>
#include <fstream>

// Создание стека
StackStr* createStackStr() {
    StackStr* stack = new StackStr;
    stack->top = nullptr;
    return stack;
}

// Добавление элемента
void pushStr(StackStr* stack, const std::string& value) {
    if (!stack) return; 

    StackNodeStr* newNode =  new StackNodeStr;
    newNode->value = value; 
    newNode->next = stack->top; // следующий элемент - текущая вершина
    stack->top = newNode;
}

// Удаление элемента
void popStr(StackStr* stack) {
    if (!stack) return;

    if(!stack->top) {
        std::cout << "Стек пуст!\n";
        return;
    }
    StackNodeStr* temp = stack->top;
    stack->top = stack->top->next;
    delete(temp);
}

// Просмотр верхнего элемента
std::string peekStr(StackStr* stack) {
    if(!stack->top) {
        std::cout << "Стек пуст!\n";
        return "";
    }
    return stack->top->value;
}

// Печать
void printStackStr(StackStr* stack) {
    if(!stack->top) {
        std::cout << "(пусто)\n";
        return;
    }
    StackNodeStr* temp = stack->top;
    std::cout << "Стек (верх -> низ): ";
    while(temp) {
        std::cout << temp->value << " ";
        temp = temp->next;
    }
    std::cout << "\n";
}

// Очистка памяти
void freeStackStr(StackStr* stack) {
    while(stack->top) {
        popStr(stack);
    }
    free(stack);
}

void saveStackToFile(StackStr* stack, const std::string& filename) {
    std::ofstream fout(filename);
    if(!fout.is_open()) {
        std::cerr << "Ошибка открытия файла для записи: " << filename << "\n";
        return;
    }

    // Пишем стек в обратном порядке, чтобы при загрузке порядок сохранился
    StackNodeStr* temp = stack->top;
    std::string lines[1000]; // фиксированный размер для примера
    int count = 0;
    while(temp) {
        lines[count++] = temp->value;
        temp = temp->next;
    }
    // Записываем снизу вверх
    for(int i = count - 1; i >= 0; i--) {
        fout << lines[i] << "\n";
    }

    fout.close();
}

// Загрузка стека из файла
void loadStackFromFile(StackStr* stack, const std::string& filename) {
    std::ifstream fin(filename);
    if(!fin.is_open()) return; // если файла нет, ничего не делаем

    std::string line;
    std::string lines[1000]; // временно храним строки
    int count = 0;

    while(std::getline(fin, line)) {
        lines[count++] = line;
    }
    fin.close();

    // Добавляем элементы в стек в правильном порядке
    for(int i = 0; i < count; i++) {
        pushStr(stack, lines[i]);
    }
}
