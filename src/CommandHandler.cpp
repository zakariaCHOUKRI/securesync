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
    }else if (cmd == "git") {
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
        } else if (gitCommand == "revert") {
            unsigned int versionNumber;
            if (stream >> versionNumber) {
                handleRevert(versionNumber);
            } else {
                std::cerr << "Invalid version number for git revert." << std::endl;
            }
        } else if (gitCommand == "help") {
            std::cout << "Available commands:\n";
            std::cout << "git login - Log in with email and password\n";
            std::cout << "git add - Add files to staging\n";
            std::cout << "git commit - Commit staged files\n";
            std::cout << "git register - Create a new account\n";
            std::cout << "git init - Initialize the repository\n";
            std::cout << "git pull - Pull changes from remote repository\n";
            std::cout << "git revert - Revert to a specific version\n";
        }
        else {
            std::cout << "Unknown git command.\n";
        }
    } else {
        std::cout << "Command not recognized.\n";
    }
}



std::string calculateFileHash(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::hash<std::string> hasher;
    return std::to_string(hasher(buffer.str()));
}




void storeFileHash(const std::string& filePath, const std::string& hash) {
    fileHashes[filePath] = hash;
}

std::string retrieveLastCommitHash(const std::string& filePath) {
    auto it = fileHashes.find(filePath);
    if (it != fileHashes.end()) {
        return it->second;
    }
    return "";  // Return empty string if hash not found
}

bool hasFileChanged(const std::string& filePath) {
    std::string currentHash = calculateFileHash(filePath);
    std::string lastHash = retrieveLastCommitHash(filePath);
    return currentHash != lastHash;
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
            // cout << entry << endl;
            if (entry.is_regular_file()){// && hasFileChanged(entry.path().string())) {
                // cout << "Staged : " <<entry.path().string() << "\n";
                stagedFiles.push_back(entry.path().string());
                // std::string fileHash = calculateFileHash(entry.path().string());
                // storeFileHash(entry.path().string(), fileHash);
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
    std::cout << "the files staged for commit are: " << endl;
    for (auto const& elem: stagedFiles) {
        cout << elem << endl;
    }
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

    // Prepare to update git.txt with commit info
    std::ostringstream commitInfo;
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    commitInfo << "\n" <<  std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "\n";
    commitInfo << "Message: " << message << "\nFiles:\n";

    // cout << commitInfo.str() <<endl;

    // Copy files and update commit info
    for (const auto& file : stagedFiles) {
        
        if (fs::path(file).filename() != "git.txt") {
            std::string destFile = versionDir.string() + "/"+ fs::path(file).filename().string();
            fs::copy(file, destFile, fs::copy_options::overwrite_existing);

            cout << "Commited : " << fs::path(file).string() << "\n";
            
            if (hasFileChanged(fs::path(file).string())){
                commitInfo << fs::path(file).filename() << "\n";
            }
            std::string fileHash = calculateFileHash(fs::path(file).string());
            storeFileHash(fs::path(file).string(), fileHash);
            
        }
    }

    // Update git.txt with commit history
    std::string contentFile = rewriteGitFileWithNewInfo(currentDirectory.string() + "/"+ "git.txt",commitInfo.str());

    // cout << currentDirectory.string() + "/"+ "git.txt" << endl;
    // std::ofstream gitFile(currentDirectory.string() + "/"+ "git.txt", std::ios::app);
    // gitFile << commitInfo.str();
    // gitFile.close();

    // Increment version number and update git.txt with the new version number
    incrementVersionNumber();
    updateGitFileVersionNumber(currentDirectory.string()+ "/"+ "git.txt", contentFile); // Modify this function to only update version number

    // Clear staged files after commit
    stagedFiles.clear();
    std::cout << "Commit successful: " << message << std::endl;
}

std::string CommandHandler::rewriteGitFileWithNewInfo(const std::string& filePath, const std::string& newInfo) {
    // Read the entire content of git.txt into a string
    std::ifstream inFile(filePath);

    std::string fileContent((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    // Modify the content as needed
    fileContent += newInfo; // Appending new information

    return fileContent;
    
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

void CommandHandler::handleRevert(unsigned int versionNumber) {
    fs::path versionDir = gitBase / currentDirectory.filename() / ("version_" + std::to_string(versionNumber));

    if (!fs::exists(versionDir) || !fs::is_directory(versionDir)) {
        std::cerr << "Version directory does not exist: " << versionDir << std::endl;
        return;
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
        inFile.close();
        return code == "1234";
    }
    inFile.close();
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

void CommandHandler::updateGitFileVersionNumber(const std::string& filePath,const std::string& contentFile) {
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
    cout << contentFile.substr(6,contentFile.length()) << endl;

    outFile << code << std::endl;
    outFile << versionNumber;
    outFile << contentFile.substr(6,contentFile.length());
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







