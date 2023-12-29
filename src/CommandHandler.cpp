#include "../include/CommandHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <map>
#include <string>


using namespace std;
namespace fs = std::filesystem;

const fs::path gitBase = "./gitBase";
std::map<std::string, std::string> fileHashes;  // A map to store file hashes

void testAll();

void handleTest() {
        testAll();  // Call the testAll function
}



void CommandHandler::executeCommand(const std::string& command) {
    try {
        std::istringstream stream(command);
        std::string cmd;
        stream >> cmd;

        if (cmd == "ls") {
            for (const auto& entry : std::filesystem::directory_iterator(currentDirectory)) {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }
        else if (cmd == "cd") {
            std::string dir;
            stream >> dir;
            changeDirectory(dir);
        } 
        else if (cmd == "test") {
            handleTest();
        }
        else if (cmd == "git") {
            std::string gitCommand;
            stream >> gitCommand;

            if (gitCommand == "login") {
                std::string email, password, temp;

                stream >> email;

                stream >> password;
                handleLogin(email, password);
            }
            else if (gitCommand == "add") {
                std::string file;
                while (stream >> file) {
                    handleAdd(file);
                }
            }
            else if (gitCommand == "commit") {
                std::string message;
                getline(stream, message); // Get the rest of the line as the commit message
                handleCommit(message);
            }
            else if (gitCommand == "register") {
                std::string email, password, confirmPass, temp;
                stream >> email >> password >> confirmPass;

                if (password == confirmPass) {
                    createAccount(email, password);
                    std::cout << "Account created successfully.\n";
                }
                else {
                    std::cout << "Passwords do not match.\n";
                }
            }
            else if (gitCommand == "init") {
                fs::path gitBaseDir = gitBase / currentDirectory.filename();
                if (!fs::exists(gitBaseDir)) {
                    fs::create_directories(gitBaseDir);
                }
                placeGitFile();
            }
            else if (gitCommand == "pull") {
                handlePull();
            }
            else if (gitCommand == "revert") {
                unsigned int versionNumber;
                if (stream >> versionNumber) {
                    handleRevert(versionNumber);
                }
                else {
                    throw std::invalid_argument("Invalid version number for git revert.");
                }
            }
            else if (gitCommand == "help") {
                std::cout << "Available commands:\n";
                std::cout << "git login - Log in with email and password\n";
                std::cout << "git add - Add files to staging\n";
                std::cout << "git commit - Commit staged files\n";
                std::cout << "git register - Create a new account\n";
                std::cout << "git init - Initialize the repository\n";
                std::cout << "git pull - Pull changes from last version\n";
                std::cout << "git revert - Revert to a specific version\n";
            }
            else {
                std::cout << "Unknown git command.\n";
            }
        }
        else {
            std::cout << "Command not recognized.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in executeCommand: " << e.what() << std::endl;
    }
}


std::string calculateFileHash(const std::string& filePath) {
    try {
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Could not open file: " + filePath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::hash<std::string> hasher;
        return std::to_string(hasher(buffer.str()));
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in calculateFileHash: " << e.what() << std::endl;
        return "";
    }
}





void storeFileHash(const std::string& filePath, const std::string& hash) {
    try {
        fileHashes[filePath] = hash;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in storeFileHash: " << e.what() << std::endl;
    }
}

std::string retrieveLastCommitHash(const std::string& filePath) {
    try {
        auto it = fileHashes.find(filePath);
        if (it != fileHashes.end()) {
            return it->second;
        }
        return "";  // Return empty string if hash not found
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in retrieveLastCommitHash: " << e.what() << std::endl;
        return "";
    }
}

bool hasFileChanged(const std::string& filePath) {
    try {
        std::string currentHash = calculateFileHash(filePath);
        std::string lastHash = retrieveLastCommitHash(filePath);
        return currentHash != lastHash;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in hasFileChanged: " << e.what() << std::endl;
        return false;
    }
}



void CommandHandler::handleAdd(const std::string& filesToAdd) {
    try {
        if (!checkGitFile()) {
            std::cerr << "git.txt not found or invalid in the current directory." << std::endl;
            return;
        }

        if (!isLoggedIn) {
            std::cout << "Error: You must be logged in to add files.\n";
            return;
        }

        if (filesToAdd == ".") {
            for (const auto& entry : fs::directory_iterator(currentDirectory)) {
                if (entry.is_regular_file() && hasFileChanged(entry.path().string())) {
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
        std::cout << "The files staged for commit are: " << std::endl;
        for (const auto& elem : stagedFiles) {
            std::cout << elem << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in handleAdd: " << e.what() << std::endl;
    }
}


void CommandHandler::handleCommit(const std::string& message) {
    try {
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

        // Prepare to update git.txt with commit info
        std::ostringstream commitInfo;
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        commitInfo << "\n" <<  std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "\n";
        commitInfo << "Message: " << message << "\nFiles:\n";

        // Copy files and update commit info
        for (const auto& file : stagedFiles) {

            if (fs::path(file).filename() != "git.txt") {
                std::string destFile = versionDir.string() + "/"+ fs::path(file).filename().string();
                fs::copy(file, destFile, fs::copy_options::overwrite_existing);

                std::cout << "Commited : " << fs::path(file).string() << "\n";

                if (hasFileChanged(fs::path(file).string())){
                    commitInfo << fs::path(file).filename() << "\n";
                }
                std::string fileHash = calculateFileHash(fs::path(file).string());
                storeFileHash(fs::path(file).string(), fileHash);

            }
        }

        // Update git.txt with commit history
        std::string contentFile = rewriteGitFileWithNewInfo(currentDirectory.string() + "/"+ "git.txt",commitInfo.str());

        // Increment version number and update git.txt with the new version number
        incrementVersionNumber();
        updateGitFileVersionNumber(currentDirectory.string()+ "/"+ "git.txt", contentFile);

        // Clear staged files after commit
        stagedFiles.clear();
        std::cout << "Commit successful: " << message << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in handleCommit: " << e.what() << std::endl;
    }
}


std::string CommandHandler::rewriteGitFileWithNewInfo(const std::string& filePath, const std::string& newInfo) {
    try {
        // Read the entire content of git.txt into a string
        std::ifstream inFile(filePath);

        std::string fileContent((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();

        // Modify the content as needed
        fileContent += newInfo; // Appending new information

        return fileContent;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in rewriteGitFileWithNewInfo: " << e.what() << std::endl;
        return "";
    }
}

void CommandHandler::createAccount(const std::string& email, const std::string& password) {
    try {
        std::ofstream accountsFile("accounts.txt", std::ios::app);
        std::string hashedPassword = hashPassword(password);
        accountsFile << email << " " << hashedPassword << std::endl;
        accountsFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in createAccount: " << e.what() << std::endl;
    }
}

std::string CommandHandler::hashPassword(const std::string& password) {
    try {
        // Simple hash for demonstration; use a better method in production
        std::hash<std::string> hasher;
        return std::to_string(hasher(password));
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in hashPassword: " << e.what() << std::endl;
        return "";
    }
}

void CommandHandler::handleLogin(const std::string& email, const std::string& password) {
    try {
        std::string hashedPassword = hashPassword(password);
        if (verifyCredentials(email, hashedPassword)) {
            std::cout << "Login successful.\n";
            isLoggedIn = true;
        } else {
            std::cout << "Login failed.\n";
            isLoggedIn = false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in handleLogin: " << e.what() << std::endl;
    }
}


void CommandHandler::handleRevert(unsigned int versionNumber) {
    try {
        fs::path versionDir = gitBase / currentDirectory.filename() / ("version_" + std::to_string(versionNumber));

        if (!fs::exists(versionDir) || !fs::is_directory(versionDir)) {
            throw std::runtime_error("Version directory does not exist: " + versionDir.string());
        }

        // Remove all files in the current directory except git.txt
        for (const auto& entry : fs::directory_iterator(currentDirectory)) {
            if (entry.is_regular_file() && entry.path().filename() != "git.txt") {
                fs::remove(entry.path());
            }
        }

        // Copy files from the version directory in gitBase to the current directory
        for (const auto& entry : fs::directory_iterator(versionDir)) {
            if (entry.is_regular_file()) {
                fs::copy(entry.path(), currentDirectory / entry.path().filename(), fs::copy_options::overwrite_existing);
            }
        }

        std::cout << "Reverted to version " << versionNumber << " from " << versionDir << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in handleRevert: " << e.what() << std::endl;
    }
}

bool CommandHandler::verifyCredentials(const std::string& email, const std::string& hashedPassword) {
    try {
        std::ifstream accountsFile("accounts.txt");
        std::string storedEmail, storedHashedPassword;
        while (accountsFile >> storedEmail >> storedHashedPassword) {
            if (storedEmail == email && storedHashedPassword == hashedPassword) {
                return true;
            }
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in verifyCredentials: " << e.what() << std::endl;
        return false;
    }
}

void CommandHandler::changeDirectory(const std::string& dir) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in changeDirectory: " << e.what() << std::endl;
    }
}

void CommandHandler::placeGitFile() {
    try {
        std::ofstream outFile(currentDirectory / "git.txt");
        outFile << "1234" << "\n" << 0;  // Writing the code to the file
        outFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in placeGitFile: " << e.what() << std::endl;
    }
}


bool CommandHandler::checkGitFile() {
    try {
        std::ifstream inFile(currentDirectory / "git.txt");
        std::string code;
        unsigned int storedVersion;
        if (inFile >> code >> storedVersion) {
            versionNumber = storedVersion;
            inFile.close();
            return code == "1234";
        }
        inFile.close();
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in checkGitFile: " << e.what() << std::endl;
        return false;
    }
}

void CommandHandler::incrementVersionNumber() {
    try {
        versionNumber++;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in incrementVersionNumber: " << e.what() << std::endl;
    }
}

std::string CommandHandler::getVersionDirectoryName() {
    try {
        return "version_" + std::to_string(versionNumber);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in getVersionDirectoryName: " << e.what() << std::endl;
        return "";
    }
}

std::string CommandHandler::getCurrentDirectory() const {
    try {
        return currentDirectory.string();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in getCurrentDirectory: " << e.what() << std::endl;
        return "";
    }
}

void CommandHandler::updateGitFileVersionNumber(const std::string& filePath, const std::string& contentFile) {
    try {
        std::ifstream inFile(filePath);
        if (!inFile.is_open()) {
            throw std::runtime_error("Unable to open git.txt for reading: " + filePath);
        }

        std::string code;
        unsigned int versionNumber;

        if (!(inFile >> code >> versionNumber)) {
            throw std::runtime_error("Error reading from git.txt: " + filePath);
        }
        inFile.close();

        // Increment the version number
        versionNumber++;

        std::ofstream outFile(filePath);
        if (!outFile.is_open()) {
            throw std::runtime_error("Unable to open git.txt for writing: " + filePath);
        }

        outFile << code << std::endl;
        outFile << versionNumber;
        outFile << contentFile.substr(6, contentFile.length());
        outFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in updateGitFileVersionNumber: " << e.what() << std::endl;
    }
}


void CommandHandler::handlePull() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in handlePull: " << e.what() << std::endl;
    }
}

