#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>

class CommandHandler {
public:
    CommandHandler() : isLoggedIn(false) {}  // Constructor to initialize isLoggedIn
    void executeCommand(const std::string& command);

private:
    bool isLoggedIn;
    void handleLogin(const std::string& email, const std::string& password);
    void handleAdd(const std::string& file);
    void handleCommit(const std::string& message);
    void createAccount(const std::string& email, const std::string& password);
    std::string hashPassword(const std::string& password);
    bool verifyCredentials(const std::string& email, const std::string& hashedPassword);
};

#endif // COMMANDHANDLER_H
