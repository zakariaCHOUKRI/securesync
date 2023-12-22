#include "FileSync.h"
#include <filesystem>
#include <fstream>  // Include for std::ifstream
#include <iostream>


namespace fs = std::filesystem;

void FileSync::synchronizeFolders(const std::string& sourcePath, const std::string& destinationPath) {
    // ... existing checks for directory existence ...

    for (const auto& entry : fs::directory_iterator(sourcePath)) {
        if (entry.is_regular_file()) {
            std::string sourceFile = entry.path().string();
            std::string destFile = destinationPath + "/" + entry.path().filename().string();

            if (areFilesDifferent(sourceFile, destFile) || !fs::exists(destFile)) {
                try {
                    // Remove the existing file in the destination if it exists
                    if (fs::exists(destFile)) {
                        fs::remove(destFile);
                    }

                    // Copy the file from source to destination
                    fs::copy(sourceFile, destFile);
                    std::cout << "File synchronized: " << destFile << std::endl;
                } catch (const fs::filesystem_error& e) {
                    std::cerr << "Error copying file: " << e.what() << '\n';
                }
            }
        }
    }
}



std::vector<std::string> FileSync::getFilesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(directoryPath))
        if (entry.is_regular_file())
            files.push_back(entry.path().string());
    return files;
}

bool FileSync::areFilesDifferent(const std::string& filePath1, const std::string& filePath2) {
    return calculateFileHash(filePath1) != calculateFileHash(filePath2);
}

std::string FileSync::calculateFileHash(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::hash<std::string> hasher;
    return std::to_string(hasher(buffer.str()));
}
