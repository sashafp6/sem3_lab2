#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;

Array* createArray(int capacity) { // создание
    Array* arr = new Array; // выделяем память под Array
    arr->data = new string[capacity]; 
    arr->size = 0; // изначально пустой (-> - доступ к члену через указатель)
    arr->capacity = capacity; // 
    return arr;
}

void pushBack(Array* arr, const string& value) { // добавление в конец
   if (arr->size >= arr->capacity){ // если массив заполнен, увеличиваем вместимость
        int newCapacity = arr->capacity * 2;
        string* newData = new string[newCapacity];

        for (int i = 0; i < arr->size; i++) // копируем старые элементы
            newData[i] = arr->data[i];

        delete[] arr->data; // освобождение старого массива

        arr->data = newData;
        arr->capacity = newCapacity;
   }

   arr->data[arr->size++] = value;
}

void insertAt(Array* arr, int index, const string& value) {
    if (index < 0 || index > arr->size) {
        cout << "Ошибка вставки.\n";
        return;
    }

    // при необходимости увеличиваем capacity
    if (arr->size >= arr->capacity) {
        int newCapacity = arr->capacity * 2;
        string* newData = new string[newCapacity];

        // копируем старые элементы
        for (int i = 0; i < arr->size; i++)
            newData[i] = arr->data[i];

        delete[] arr->data;
        arr->data = newData;
        arr->capacity = newCapacity;
    }

    // сдвигаем вправо элементы
    for (int i = arr->size; i > index; i--)
        arr->data[i] = arr->data[i - 1];

    arr->data[index] = value;
    arr->size++;
}

string getAt(Array* arr, int index) { // получение по индексу
    if (index >= 0 && index < arr->size)
        return arr->data[index]; // возвращаем элемент
    cout << "Ошибка: индекс вне диапазона.\n";
    return "";
}

void removeAt(Array* arr, int index) { // удаление по индексу
    if (index < 0 || index >= arr->size) {
        cout << "Ошибка удаления.\n";
        return;
    }
    for (int i = index; i < arr->size - 1; i++) // сдвиг элементов влево
        arr->data[i] = arr->data[i + 1];
    arr->size--;
}

void setAt(Array* arr, int index, const string& value) { // замена по индексу
    if (index >= 0 && index < arr->size)
        arr->data[index] = value;
    else
        cout << "Ошибка: индекс вне диапазона.\n";
}

void printArray(Array* arr) { // вывод массива
    for (int i = 0; i <  arr->size; i++)
        cout << arr->data [i] << " "; // добавляем и увеличиваем размер
    cout << endl;
}

void loadArrayFromFile(Array* arr, const char* filename) {
    ifstream fin(filename); // открываем файл для чтения
    if(!fin.is_open()) return; // если не открылся

    string line;
    while(getline(fin, line)) { // читаем построчно
        pushBack(arr, line);
    }

    fin.close(); // закрываем файл
}

void saveArrayToFile(Array* arr, const char* filename) {
    ofstream fout(filename);
    if(!fout.is_open()) return;

    for(int i = 0; i < arr->size; i++) {
        fout << arr->data[i] << "\n"; // записываем элементы
    }
    fout.close();
}

// Добавление элемента сразу в массив и файл
void pushBackToFile(Array* arr, const char* filename, const string& value) {
    pushBack(arr, value);

    // дозаписываем только новый элемент
    ofstream fout(filename, std::ios::app); 
    if(fout.is_open()) fout << value << "\n";
    fout.close();
}

void freeArray(Array* arr) { // освобождение памяти
    delete[] arr->data;
    delete arr;
}
