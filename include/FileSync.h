#ifndef FILESYNC_H
#define FILESYNC_H

#include <string>
#include <vector>

class FileSync {
public:
    void synchronizeFolders(const std::string& sourcePath, const std::string& destinationPath);
    static std::string calculateFileHash(const std::string& filePath);

private:
    std::vector<std::string> getFilesInDirectory(const std::string& directoryPath);
    bool areFilesDifferent(const std::string& filePath1, const std::string& filePath2);
};

#endif // FILESYNC_H
