#include "storage_engine.h"
#include <iostream>

void BlinkDB::set(const std::string& key, const std::string& value) {
    storage[key] = value;
//    std::cout << "OK\n";
}

std::string BlinkDB::get(const std::string& key) {
    if (storage.find(key) != storage.end()) {
        return storage[key];
    }
    return "NULL";
}

void BlinkDB::del(const std::string& key) {
    if (storage.erase(key)) {
        std::cout << "Deleted\n";
    } else {
        std::cout << "Does not exist\n";
    }
}
