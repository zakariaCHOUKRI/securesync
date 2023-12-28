#include "../include/CommandHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <functional>

using namespace std;
namespace fs = std::filesystem;

const fs::path gitBase = "./gitBase";



void CommandHandler::executeCommand(const std::string& command) {
    std::istringstream stream(command);
    std::string cmd;
    stream >> cmd;

    if (cmd == "cd") {
        std::string dir;
        stream >> dir;
        changeDirectory(dir);
    } else if (cmd == "git") {
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
        } else if (gitCommand == "register") {
            std::string email, password, confirmPass, temp;
            stream >> email >> password >> confirmPass;
            
            if (password == confirmPass) {
                createAccount(email, password);
                std::cout << "Account created successfully.\n";
            } else {
                std::cout << "Passwords do not match.\n";
            }
        } else if (gitCommand == "init") {
            fs::path gitBaseDir = gitBase / currentDirectory.filename();
            if (!fs::exists(gitBaseDir)) {
                fs::create_directories(gitBaseDir);
            }
            placeGitFile();
        } else if (gitCommand == "pull") {
            handlePull();
        }
        else {
            std::cout << "Unknown git command.\n";
        }
    } else {
        std::cout << "Command not recognized.\n";
    }
}


void CommandHandler::handleAdd(const std::string& filesToAdd) {
    if (!checkGitFile()) {
        std::cerr << "git.txt not found or invalid in the current directory." << std::endl;
        return;
    }
    
    if (!isLoggedIn) {
        std::cout << "Error: You must be logged in to add files.\n";
        return;
    }
    if (filesToAdd == ".") {
        // Add logic to stage all files in the current directory
        for (const auto& entry : fs::directory_iterator(currentDirectory)) {
            if (entry.is_regular_file()) {
                stagedFiles.push_back(entry.path().string());
            }
        }
    } else {
        std::istringstream iss(filesToAdd);
        std::string file;
        while (iss >> file) {
            stagedFiles.push_back(file);
        }
    }

    std::cout << "Staged files for commit.\n";
}

void CommandHandler::handleCommit(const std::string& message) {
    if (!checkGitFile()) {
        std::cerr << "git.txt not found or invalid in the current directory." << std::endl;
        return;
    }

    if (!isLoggedIn) {
        std::cout << "Error: You must be logged in to add files.\n";
        return;
    }

    fs::path gitBaseDir = gitBase / currentDirectory.filename();
    if (!fs::exists(gitBaseDir)) {
        fs::create_directories(gitBaseDir);
    }

    std::string versionDirName = getVersionDirectoryName();
    fs::path versionDir = gitBaseDir / versionDirName;
    fs::create_directory(versionDir);

    // Copy staged files to the version folder
    for (const auto& file : stagedFiles) {
        std::string destFile = versionDir.string() + "/" + fs::path(file).filename().string();
        fs::copy(file, destFile, fs::copy_options::overwrite_existing);
        cout << destFile << endl;
    }

    // Read the current git.txt for version number
    std::ifstream inFile(currentDirectory / "git.txt");
    if (!inFile.is_open()) {
        std::cerr << "Unable to open git.txt for reading." << std::endl;
        return;
    }

    unsigned int prevVersionNumber;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip the first line
    inFile >> prevVersionNumber; // Read the previous version number
    inFile.close();

    // Open the current git.txt for writing and append mode
    std::ofstream outFile(currentDirectory / "git.txt");
    if (!outFile.is_open()) {
        std::cerr << "Unable to open git.txt for writing." << std::endl;
        return;
    }

    // Write the magic number
    outFile << "1234\n";

    // Write the updated version number
    outFile << prevVersionNumber + 1 << "\n";

    // Get current timestamp for the commit
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* timestamp = std::localtime(&now);

    // Append commit information
    outFile << std::put_time(timestamp, "%Y-%m-%d %H:%M:%S") << "\n";
    for (const auto& file : stagedFiles) {
        outFile << fs::path(file).filename().string() << "\n";
    }
    outFile << "Message: " << message << "\n";

    outFile.close();

    // Clear staged files after commit
    stagedFiles.clear();
    std::cout << "Commit successful: " << message << std::endl;
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

void CommandHandler::changeDirectory(const std::string& dir) {
    if (dir == "..") {
        currentDirectory = currentDirectory.parent_path();
    } else {
        fs::path newDir = currentDirectory / dir;
        if (fs::exists(newDir) && fs::is_directory(newDir)) {
            currentDirectory = newDir;
        } else {
            std::cerr << "Directory does not exist: " << newDir << std::endl;
        }
    }
    // std::cout << "Current directory: " << currentDirectory << std::endl;
}

void CommandHandler::placeGitFile() {
    std::ofstream outFile(currentDirectory / "git.txt");
    outFile << "1234" <<"\n" << 0;  // Writing the code to the file
    outFile.close();
}

bool CommandHandler::checkGitFile() {
    std::ifstream inFile(currentDirectory / "git.txt");
    std::string code;
    unsigned int storedVersion;
    if (inFile >> code >> storedVersion) {
        versionNumber = storedVersion;
        return code == "1234";
    }
    return false;
}

void CommandHandler::incrementVersionNumber() {
    versionNumber++;
}

std::string CommandHandler::getVersionDirectoryName() {
    return "version_" + std::to_string(versionNumber);
}

std::string CommandHandler::getCurrentDirectory() const {
    return currentDirectory.string();
}

void CommandHandler::updateGitFileVersionNumber(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open git.txt for reading." << std::endl;
        return;
    }

    std::string code;
    unsigned int versionNumber;
    
    if (!(inFile >> code >> versionNumber)) {
        std::cerr << "Error reading from git.txt." << std::endl;
        inFile.close();
        return;
    }
    inFile.close();

    // Increment the version number
    versionNumber++;

    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open git.txt for writing." << std::endl;
        return;
    }

    outFile << code << std::endl;
    outFile << versionNumber;
    outFile.close();
}

void CommandHandler::handlePull() {
    if (!checkGitFile()) {
        std::cerr << "git.txt not found or invalid in the current directory." << std::endl;
        return;
    }

    unsigned int currentVersion = versionNumber;
    if (currentVersion == 0) {
        std::cout << "No previous versions to pull.\n";
        return;
    }

    unsigned int previousVersion = currentVersion - 1;
    fs::path gitBaseDir = gitBase / currentDirectory.filename();
    fs::path previousVersionDir = gitBaseDir / ("version_" + std::to_string(previousVersion));

    if (!fs::exists(previousVersionDir)) {
        std::cout << "Version " << previousVersion << " does not exist in gitBase.\n";
        return;
    }

    // Clear existing files in the current working directory
    for (const auto& entry : fs::directory_iterator(currentDirectory)) {
        if (entry.is_regular_file() && entry.path().filename() != "git.txt") {
            fs::remove(entry.path());
        }
    }

    // Copy files (except git.txt) from the previous version to the current working directory
    for (const auto& entry : fs::directory_iterator(previousVersionDir)) {
        if (entry.is_regular_file() && entry.path().filename() != "git.txt") {
            fs::copy(entry.path(), currentDirectory / entry.path().filename());
        }
    }

    std::cout << "Pull successful. Pulled changes from version " << previousVersion << ".\n";
}

