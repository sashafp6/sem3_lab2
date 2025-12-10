#include "hashtable.h"
#include <fstream>
#include <functional>
#include <algorithm>

// ДВОЙНОЕ ХЭШИРОВАНИЕ 

int hash1(const std::string& key, int size) { // ostatok ot deleniya
    return std::hash<std::string>{}(key) % size;
}

int hash2(const std::string& key, int size) {
    return 1 + (std::hash<std::string>{}(key) / size) % (size - 1); // return count from 1 to size -1, ne bilo zaciklivaniya
}

void initHashTableDouble(HashTable& ht, int initial_size) {
    ht.size = initial_size;
    ht.count = 0;
    ht.table.assign(ht.size, {EMPTY_KEY, ""});
}

void insertDouble(HashTable& ht, const std::string& key, const std::string& value) { // proverka na dublikat
    if (!searchDouble(ht, key).empty()){
        std::cout << "Error: element with this name " << key << " already exists\n";
        return;
    }

    if (ht.count >= ht.size * MAX_LOAD_FACTOR) { // dlya uvilecheniya razmera koef zapoln
        int old_size = ht.size;
        std::vector<HashEntry> old_table = ht.table;

        ht.size *= 2;
        ht.count = 0;
        ht.table.assign(ht.size, {EMPTY_KEY, ""});
        for (auto& e : old_table) {
            if (!e.key.empty() && e.key != DELETED_KEY)
                insertDouble(ht, e.key, e.value);
        }
    }

    int i = 0;
    int index1 = hash1(key, ht.size);
    int index2 = hash2(key, ht.size);
    int index = index1;
    int first_deleted_index = -1;

    while (!ht.table[index].key.empty()) {
        if (ht.table[index].key == key) {
            ht.table[index].value = value;
            return;
        }
        if (ht.table[index].key == DELETED_KEY && first_deleted_index == -1)
            first_deleted_index = index;
        i++;
        index = (index1 + i * index2) % ht.size;
    }

    if (first_deleted_index != -1)
        ht.table[first_deleted_index] = {key, value};
    else
        ht.table[index] = {key, value};

    ht.count++;
}

std::string searchDouble(const HashTable& ht, const std::string& key) {
    int i = 0;
    int index1 = hash1(key, ht.size);
    int index2 = hash2(key, ht.size);
    int index = index1;

    while (!ht.table[index].key.empty()) {
        if (ht.table[index].key == key)
            return ht.table[index].value;
        i++;
        index = (index1 + i * index2) % ht.size;
        if (i >= ht.size) break;
    }
    return "";
}

void removeDouble(HashTable& ht, const std::string& key) {
    int i = 0;
    int index1 = hash1(key, ht.size);
    int index2 = hash2(key, ht.size);
    int index = index1;
    while (!ht.table[index].key.empty()) {
        if (ht.table[index].key == key) {
            ht.table[index] = {DELETED_KEY, ""};
            ht.count--;
            return;
        }
        i++;
        index = (index1 + i * index2) % ht.size;
        if (i >= ht.size) break;
    }
}

void printDouble(const HashTable& ht) {
    std::cout << "\n--- Двойное хэширование ---\n";
    for (int i = 0; i < ht.size; i++) {
        if (!ht.table[i].key.empty() && ht.table[i].key != DELETED_KEY)
            std::cout << "[" << i << "] " << ht.table[i].key << " : " << ht.table[i].value << "\n";
    }
}

void saveToFileDouble(const HashTable& ht, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& e : ht.table) {
        if (!e.key.empty() && e.key != DELETED_KEY)
            file << e.key << ";" << e.value << "\n";
    }
}

void loadFromFileDouble(HashTable& ht, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        size_t pos = line.find(';');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            insertDouble(ht, key, value);
        }
    }
}

// КУКУШКИНО ХЭШИРОВАНИЕ

int cuckoohash1(const std::string& key, int size) {
    return std::hash<std::string>{}(key) % size;
}

int cuckoohash2(const std::string& key, int size) {
    return (std::hash<std::string>{}(key) / size) % size;
}

void initCuckoo(CuckooHashTable& ht, int initial_size) {
    ht.size = initial_size;
    ht.table.assign(ht.size, {EMPTY_KEY, ""});
}

void rehashCuckoo(CuckooHashTable& ht) {std::vector<HashEntry> old = ht.table;
    ht.size *= 2;
    ht.table.assign(ht.size, {EMPTY_KEY, ""});
    for (auto& e : old) {
        if (!e.key.empty() && e.key != DELETED_KEY)
            insertCuckoo(ht, e.key, e.value);
    }
}

void insertCuckoo(CuckooHashTable& ht, const std::string& key, const std::string& value) {
    if (!searchCuckoo(ht, key).empty()){
        std::cout << "Error: dog with this name " << key << " already exists\n";
        return;
    }

    std::string curKey = key;
    std::string curVal = value;

    for (int tries = 0; tries < MAX_RELOCATIONS; tries++) {
        int i1 = cuckoohash1(curKey, ht.size);
        if (ht.table[i1].key.empty() || ht.table[i1].key == DELETED_KEY) {
            ht.table[i1] = {curKey, curVal};
            return;
        }
        std::swap(curKey, ht.table[i1].key);
        std::swap(curVal, ht.table[i1].value);

        int i2 = cuckoohash2(curKey, ht.size);
        if (ht.table[i2].key.empty() || ht.table[i2].key == DELETED_KEY) {
            ht.table[i2] = {curKey, curVal};
            return;
        }
        std::swap(curKey, ht.table[i2].key);
        std::swap(curVal, ht.table[i2].value);
    }

    rehashCuckoo(ht);
    insertCuckoo(ht, curKey, curVal);
}

std::string searchCuckoo(const CuckooHashTable& ht, const std::string& key) {
    int i1 = cuckoohash1(key, ht.size);
    int i2 = cuckoohash2(key, ht.size);
    if (ht.table[i1].key == key) return ht.table[i1].value;
    if (ht.table[i2].key == key) return ht.table[i2].value;
    return "";
}

void removeCuckoo(CuckooHashTable& ht, const std::string& key) {
    int i1 = cuckoohash1(key, ht.size);
    if (ht.table[i1].key == key) {
        ht.table[i1] = {DELETED_KEY, ""};
        return;
    }
    int i2 = cuckoohash2(key, ht.size);
    if (ht.table[i2].key == key) {
        ht.table[i2] = {DELETED_KEY, ""};
        return;
    }
}

void printCuckoo(const CuckooHashTable& ht) {
    std::cout << "\n--- Кукушкино хэширование ---\n";
    for (int i = 0; i < ht.size; i++) {
        if (!ht.table[i].key.empty() && ht.table[i].key != DELETED_KEY)
            std::cout << "[" << i << "] " << ht.table[i].key << " : " << ht.table[i].value << "\n";
    }
}

void saveToFileCuckoo(const CuckooHashTable& ht, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& e : ht.table) {
        if (!e.key.empty() && e.key != DELETED_KEY)
            file << e.key << ";" << e.value << "\n";
    }
}

void loadFromFileCuckoo(CuckooHashTable& ht, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        size_t pos = line.find(';');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            insertCuckoo(ht, key, value);
        }
    }
}
