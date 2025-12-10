
#ifndef ARRAY_H
#define ARRAY_h
#include <string>

struct Array{
    std::string* data; // массив строк
    int size; // текущий размер массива
    int capacity; // максимальная вместимость
 
};

Array* createArray(int capacity);
void pushBack(Array* arr, const std::string& value);
void insertAt(Array* arr, int index, const std::string& value);
std::string getAt(Array* arr, int index);
void removeAt(Array* arr, int index);
void setAt(Array* arr, int index, const std::string& value);
void printArray(Array* arr);
void freeArray(Array* arr);

void loadArrayFromFile(Array* arr, const char* filename);
void saveArrayToFile(Array* arr, const char* filename);
void pushBackToFile(Array* arr, const char* filename, const std::string& value);

#endif
