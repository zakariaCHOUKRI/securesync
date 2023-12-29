#include "CommandHandler.h"
#include <iostream>
#include <cassert>
#include <filesystem>
#include <fstream>

using namespace std;

string absolutePath = std::filesystem::absolute(std::filesystem::path(__FILE__).parent_path()).string();
void testHandleLogin() {
    CommandHandler commandHandler(absolutePath);
    commandHandler.createAccount("test@example.com", "password");
    assert(commandHandler.verifyCredentials("test@example.com", commandHandler.hashPassword("password")) == true);
    std::cout << "testHandleLogin passed.\n";
}


void testCreateAccount() {
    CommandHandler commandHandler(absolutePath);
    commandHandler.createAccount("newuser@example.com", "newpassword");
    assert(commandHandler.verifyCredentials("newuser@example.com", commandHandler.hashPassword("newpassword")) == true);
    std::cout << "testCreateAccount passed.\n";
}

void testHashPassword() {
    CommandHandler commandHandler(absolutePath);
    std::string password = "mypassword";
    std::string hashed = commandHandler.hashPassword(password);
    assert(!hashed.empty() && hashed != password);
    std::cout << "testHashPassword passed.\n";
}

void testChangeDirectory() {
    CommandHandler commandHandler(absolutePath);
    commandHandler.changeDirectory("gui");
    // cout << commandHandler.getCurrentDirectory() << endl;
    assert(commandHandler.getCurrentDirectory() == "C:\\Users\\21269\\Desktop\\securesync\\src\\gui");
    std::cout << "testChangeDirectory passed.\n";
}

void testPlaceGitFile() {
    CommandHandler commandHandler(absolutePath);
    commandHandler.placeGitFile();
    std::cout << "testPlaceGitFile passed (manual verification required).\n";
}

void testIncrementVersionNumber() {
    CommandHandler commandHandler(absolutePath);
    unsigned int beforeIncrement = commandHandler.versionNumber;
    commandHandler.incrementVersionNumber();
    assert(commandHandler.versionNumber == beforeIncrement + 1);
    std::cout << "testIncrementVersionNumber passed.\n";
}


void testAll() {
    testHandleLogin();
    
    testCreateAccount();
    testHashPassword();
    testChangeDirectory();
    testPlaceGitFile();
    testIncrementVersionNumber();

    std::cout << "All tests completed.\n";
}