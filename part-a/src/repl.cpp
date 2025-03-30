#include <iostream>
#include <string>
#include "storage_engine.h"

int main() {
    BlinkDB db;
    std::string command, key, value;

    while (true) {
        std::cout << "User> ";
        std::cin >> command;

        if (command == "SET") {
            std::cin >> key >> value;
            db.set(key, value);
        } 
        else if (command == "GET") {
            std::cin >> key;
            std::cout << db.get(key) << std::endl;
        } 
        else if (command == "DEL") {
            std::cin >> key;
            db.del(key);
        } 
        else if (command == "EXIT") {
            break;
        } 
        else {
            std::cout << "Invalid command\n";
        }
    }

    return 0;
}
