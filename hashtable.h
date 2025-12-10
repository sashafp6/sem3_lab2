#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>

// --- Константы ---
const double MAX_LOAD_FACTOR = 0.9;
const int MAX_RELOCATIONS = 10;

const std::string EMPTY_KEY = "";
const std::string DELETED_KEY = "<deleted>";

// --- Общая структура для пары ключ-значение ---
struct HashEntry {
    std::string key;
    std::string value;
};

// === ДВОЙНОЕ ХЭШИРОВАНИЕ ===

struct HashTable {
    int size;
    int count;
    std::vector<HashEntry> table;
};

void initHashTableDouble(HashTable& ht, int initial_size);
void insertDouble(HashTable& ht, const std::string& key, const std::string& value);
std::string searchDouble(const HashTable& ht, const std::string& key);
void removeDouble(HashTable& ht, const std::string& key);
void printDouble(const HashTable& ht);
void saveToFileDouble(const HashTable& ht, const std::string& filename);
void loadFromFileDouble(HashTable& ht, const std::string& filename);

//  Хэш-функции 
int hash1(const std::string& key, int size);
int hash2(const std::string& key, int size);

// === КУКУШКИНО ХЭШИРОВАНИЕ 
struct CuckooHashTable {
    int size;
    std::vector<HashEntry> table;
};

void initCuckoo(CuckooHashTable& ht, int initial_size);
void insertCuckoo(CuckooHashTable& ht, const std::string& key, const std::string& value);
std::string searchCuckoo(const CuckooHashTable& ht, const std::string& key);
void removeCuckoo(CuckooHashTable& ht, const std::string& key);
void printCuckoo(const CuckooHashTable& ht);
void saveToFileCuckoo(const CuckooHashTable& ht, const std::string& filename);
void loadFromFileCuckoo(CuckooHashTable& ht, const std::string& filename);
int cuckoohash1(const std::string& key, int size);
int cuckoohash2(const std::string& key, int size);

#endif
