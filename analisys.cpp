#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "hashtable.h"  // здесь подключаются все функции хеширования

// Функция для проведения анализа производительности
void performAnalysis() {
    int N = 10;  // число заранее заданных элементов
    int M = 5;   // количество поисков

    // Заранее заданные элементы 
    std::vector<std::string> data = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon"
    };

    // Ключи для поиска 
    std::vector<std::string> searchKeys = {
        "banana", "fig", "kiwi", "orange", "apple"
    };

    //  ДВОЙНОЕ ХЭШИРОВАНИЕ 
    HashTable htDouble;
    initHashTableDouble(htDouble, 2 * N);

    auto start_insert_double = std::chrono::high_resolution_clock::now();
    for (auto& key : data)
        insertDouble(htDouble, key, key);
    auto end_insert_double = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insert_time_double = end_insert_double - start_insert_double;

    auto start_search_double = std::chrono::high_resolution_clock::now();
    int foundDouble = 0;
    for (auto& key : searchKeys)
        if (!searchDouble(htDouble, key).empty()) foundDouble++;
    auto end_search_double = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> search_time_double = end_search_double - start_search_double;

    //  КУКУШКИНО ХЭШИРОВАНИЕ 
    CuckooHashTable htCuckoo;
    initCuckoo(htCuckoo, 2 * N);

    auto start_insert_cuckoo = std::chrono::high_resolution_clock::now();
    for (auto& key : data)
        insertCuckoo(htCuckoo, key, key);
    auto end_insert_cuckoo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insert_time_cuckoo = end_insert_cuckoo - start_insert_cuckoo;

    auto start_search_cuckoo = std::chrono::high_resolution_clock::now();
    int foundCuckoo = 0;
    for (auto& key : searchKeys)
        if (!searchCuckoo(htCuckoo, key).empty()) foundCuckoo++;
    auto end_search_cuckoo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> search_time_cuckoo = end_search_cuckoo - start_search_cuckoo;

    // ВЫВОД РЕЗУЛЬТАТОВ 
    std::cout << "\n=== Эмпирический анализ ===\n";
    std::cout << "Количество элементов (N): " << N << "\n";
    std::cout << "Количество поисков (M): " << M << "\n\n";

    std::cout << "----- Двойное хэширование -----\n";
    std::cout << "Время вставки: " << insert_time_double.count() << " сек\n";
    std::cout << "Время поиска: " << search_time_double.count() << " сек\n";
    std::cout << "Найдено элементов: " << foundDouble << "\n\n";

    std::cout << "----- Кукушкино хэширование -----\n";
    std::cout << "Время вставки: " << insert_time_cuckoo.count() << " сек\n";
    std::cout << "Время поиска: " << search_time_cuckoo.count() << " сек\n";
    std::cout << "Найдено элементов: " << foundCuckoo << "\n";
}
