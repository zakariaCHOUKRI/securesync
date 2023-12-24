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

// int main() {
//     CommandHandler commandHandler;
//     std::string command;

//     while (true) {
//         std::cout << "> "; // Display a command prompt
//         std::getline(std::cin, command);

//         // Check for a special command to exit the loop, e.g., "exit"
//         if (command == "exit") {
//             break;
//         }

//         commandHandler.executeCommand(command);
//     }

//     return 0;
// }

// int main() {
//     CommandHandler commandHandler;
//     FileSync fileSync;

//     // Example usage of file synchronization
//     std::string sourcePath = "testSync/dir1";
//     std::string destinationPath = "testSync/dir2";
//     fileSync.synchronizeFolders(sourcePath, destinationPath);

//     // Existing code for command handling...
//     return 0;
// }
