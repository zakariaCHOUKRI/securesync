#include <iostream>
#include "CommandHandler.h"
#include "FileSync.h"
#include <filesystem>

int main() {
    std::filesystem::path currentPath = std::filesystem::absolute(std::filesystem::path(__FILE__).parent_path());
    CommandHandler commandHandler(currentPath.string());
    std::string command;

    while (true) {
        std::cout << commandHandler.getCurrentDirectory() << " $ "; // Display current directory
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        commandHandler.executeCommand(command);
    }

    return 0;
}
