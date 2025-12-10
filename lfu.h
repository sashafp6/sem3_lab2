#pragma once
#include "doublylinked.h"
#include <string>

struct LFUCache {
    int capacity;
    DoublyList* list;

    LFUCache(int cap);
    ~LFUCache();

    void SET(const std::string& key, const std::string& value);
    std::string GET(const std::string& key);
    void printCache();

private:
    NodeD* findMinFreqNode();
    void parseValue(const std::string& str, std::string& key, std::string& val, int& freq);
    std::string makeValue(const std::string& key, const std::string& val, int freq);
    void removeNodeD(NodeD* node);
};
