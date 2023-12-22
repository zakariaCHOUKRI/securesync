#include "../include/CommandHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

using namespace std;

void CommandHandler::executeCommand(const std::string& command) {
    std::istringstream stream(command);
    std::string cmd;
    stream >> cmd;

    if (cmd == "git") {
        std::string gitCommand;
        stream >> gitCommand;

        if (gitCommand == "login") {
            std::string email, password, temp;
            
            stream >> email ;
            
            stream >> password;
            handleLogin(email, password);
        } else if (gitCommand == "add") {
            std::string file;
            while (stream >> file) {
                handleAdd(file);
            }
        } else if (gitCommand == "commit") {
            std::string message;
            getline(stream, message); // Get the rest of the line as the commit message
            handleCommit(message);
        } else if (gitCommand == "createaccount") {
            std::string email, password, confirmPass, temp;
            stream >> email >> password >> confirmPass;
            
            if (password == confirmPass) {
                createAccount(email, password);
                std::cout << "Account created successfully.\n";
            } else {
                std::cout << "Passwords do not match.\n";
            }
        } 
        
        else {
            std::cout << "Unknown git command.\n";
        }
    } else {
        std::cout << "Command not recognized.\n";
    }
}


void CommandHandler::handleAdd(const std::string& file) {

    if (!isLoggedIn) {
        std::cout << "Error: You must be logged in to add files.\n";
        return;
    }
    std::cout << "Adding file: " << file << "\n";
    // Add file handling logic here

    std::cout << "Adding file: " << file << " to staging area.\n";

}

void CommandHandler::handleCommit(const std::string& message) {

    if (!isLoggedIn) {
        std::cout << "Error: You must be logged in to add files.\n";
        return;
    }
    
    std::cout << "Committing with message: " << message << "\n";
    // Add commit logic here

    std::cout << "Committing staged files with message: " << message << "\n";

}

void CommandHandler::createAccount(const std::string& email, const std::string& password) {
    std::ofstream accountsFile("accounts.txt", std::ios::app);
    std::string hashedPassword = hashPassword(password);
    accountsFile << email << " " << hashedPassword << std::endl;
    accountsFile.close();
}

std::string CommandHandler::hashPassword(const std::string& password) {
    // Simple hash for demonstration; use a better method in production
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

void CommandHandler::handleLogin(const std::string& email, const std::string& password) {
    std::string hashedPassword = hashPassword(password);
    if (verifyCredentials(email, hashedPassword)) {
        std::cout << "Login successful.\n";
        isLoggedIn = true;
    } else {
        std::cout << "Login failed.\n";
        isLoggedIn = false;
    }
}

bool CommandHandler::verifyCredentials(const std::string& email, const std::string& hashedPassword) {
    std::ifstream accountsFile("accounts.txt");
    std::string storedEmail, storedHashedPassword;
    while (accountsFile >> storedEmail >> storedHashedPassword) {
        if (storedEmail == email && storedHashedPassword == hashedPassword) {
            return true;
        }
    }
    return false;
}
