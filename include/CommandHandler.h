#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>
#include <vector>
#include <filesystem>


class CommandHandler {
public:
    CommandHandler(const std::string& startingDirectory)
    : isLoggedIn(false), stagedFiles(), versionNumber(0), currentDirectory(startingDirectory) {
    // Optionally, you can add additional checks or initializations here
}
    void executeCommand(const std::string& command);
    bool isLoggedIn;
    std::vector<std::string> stagedFiles;
    std::filesystem::path currentDirectory;
    unsigned int versionNumber;
    std::filesystem::path gitBaseAbsolutePath;

    void handleLogin(const std::string& email, const std::string& password);
    void handleAdd(const std::string& file);
    void handleCommit(const std::string& message);
    void createAccount(const std::string& email, const std::string& password);
    std::string hashPassword(const std::string& password);
    bool verifyCredentials(const std::string& email, const std::string& hashedPassword);
    void changeDirectory(const std::string& dir);
    void placeGitFile();
    bool checkGitFile();
    void incrementVersionNumber();
    std::string getVersionDirectoryName();
    std::string getCurrentDirectory() const;
    void updateGitFileVersionNumber(const std::string& filePath,const std::string&);
    void handlePull();
    std::string rewriteGitFileWithNewInfo(const std::string& filePath, const std::string& newInfo);
    void handleRevert(unsigned int versionNumber);



};

#endif // COMMANDHANDLER_H
