#include "lfu.h"
#include <iostream>

// Конструктор
LFUCache::LFUCache(int cap) {
    capacity = cap;
    list = createDoublyList();
}

// Деструктор
LFUCache::~LFUCache() {
    freeDoubly(list);
}

// вставка строки 
void LFUCache::parseValue(const std::string& str, std::string& key, std::string& val, int& freq) {
    size_t first = str.find(':');
    size_t second = str.rfind(':');
    key = str.substr(0, first);
    val = str.substr(first + 1, second - first - 1);
    freq = std::stoi(str.substr(second + 1));
}

// Создание строки "key:value:freq"
std::string LFUCache::makeValue(const std::string& key, const std::string& val, int freq) {
    return key + ":" + val + ":" + std::to_string(freq);
}

// Удаление конкретного узла по указателю
void LFUCache::removeNodeD(NodeD* node) {
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    else list->head = node->next;

    if (node->next) node->next->prev = node->prev;
    else list->tail = node->prev;

    delete node;
}

// Найти узел с минимальной частотой
NodeD* LFUCache::findMinFreqNode() {
    NodeD* current = list->head;
    if (!current) return nullptr;

    NodeD* minNode = current;
    std::string key, val;
    int freq, minFreq;
    parseValue(current->value, key, val, minFreq);

    current = current->next;
    while (current) {
        parseValue(current->value, key, val, freq);
        if (freq < minFreq) {
            minFreq = freq;
            minNode = current;
        }
        current = current->next;
    }
    return minNode;
}

// Установка ключа
void LFUCache::SET(const std::string& key, const std::string& value) {
    NodeD* current = list->head;
    std::string k, v;
    int freq;

    // Если ключ уже есть, обновляем значение и частоту на месте
    while (current) {
        parseValue(current->value, k, v, freq);
        if (k == key) {
            freq++;
            current->value = makeValue(k, value, freq);
            return;
        }
        current = current->next;
    }

    // Если кэш заполнен, удаляем узел с минимальной частотой
    int count = 0;
    current = list->head;
    while (current) { count++; current = current->next; }

    if (count >= capacity) {
        NodeD* minNode = findMinFreqNode();
        removeNodeD(minNode);
    }

    // Добавляем новый узел
    pushBackD(list, makeValue(key, value, 1));
}

// Получение ключа
std::string LFUCache::GET(const std::string& key) {
    NodeD* current = list->head;
    std::string k, v;
    int freq;

    while (current) {
        parseValue(current->value, k, v, freq);
        if (k == key) {
            freq++;
            current->value = makeValue(k, v, freq); // увеличиваем частоту на месте
            return v;
        }
        current = current->next;
    }
    return "-1";
}

// Печать кэша
void LFUCache::printCache() {
    std::cout << "Состояние кэша:\n";
    printDoubly(list);
}
