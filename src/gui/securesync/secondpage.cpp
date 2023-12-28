#include "secondpage.h"
#include "ui_secondpage.h"
#include <qfiledialog.h>
#include "../../../include/CommandHandler.h"
#include <iostream>
#include <QMessageBox>

namespace fs = std::filesystem;
const fs::path gitBase = "./gitBase";

static QString chosenDirectory;
static std::vector<std::string> localStagedFiles;

secondPage::secondPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::secondPage)
{
    ui->setupUi(this);

    ui->gitInitButton->setEnabled(false);
    ui->gitAddButton->setEnabled(false);
    ui->gitPullButton->setEnabled(false);
    ui->gitCommitButton->setEnabled(false);
}

secondPage::~secondPage()
{
    delete ui;
}

void secondPage::on_chooseDirectoryButton_clicked()
{
    chosenDirectory = QFileDialog::getExistingDirectory(this, "Select a Directory");

    if (!chosenDirectory.isEmpty()) {
        ui->directoryLineEdit->setText(chosenDirectory);
        updateFileList(chosenDirectory);

        std::filesystem::path currentPath2 = std::filesystem::absolute(std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path());
        CommandHandler commandHandler2(currentPath2.string());

        commandHandler2.currentDirectory = chosenDirectory.toStdString();
        // std::cout << commandHandler2.currentDirectory.string() << std::endl;

        if (commandHandler2.checkGitFile()) {
            ui->gitAddButton->setEnabled(true);
            ui->gitPullButton->setEnabled(true);
            ui->gitCommitButton->setEnabled(true);
        } else {
            ui->gitInitButton->setEnabled(true);
        }
    }
}

void secondPage::updateFileList(const QString &directoryPath)
{
    // Clear the existing items in the list widget
    ui->fileListWidget->clear();

    // Create a QDir object for the selected directory
    QDir directory(directoryPath);

    // Get the list of files in the directory
    QFileInfoList fileList = directory.entryInfoList();

    // Iterate through the files and add them to the list widget
    for (const QFileInfo &fileInfo : fileList) {
        ui->fileListWidget->addItem(fileInfo.fileName());
    }
}

void secondPage::on_gitInitButton_clicked()
{
    ui->gitInitButton->setEnabled(false);
    ui->gitAddButton->setEnabled(true);
    ui->gitPullButton->setEnabled(true);
    ui->gitCommitButton->setEnabled(true);

    CommandHandler commandHandler4(chosenDirectory.toStdString());

    // std::cout << gitBase << std::endl;

    fs::path gitBaseDir = fs::path("gitBase") / fs::path(commandHandler4.currentDirectory.string()).filename();
    // std::cout << gitBaseDir << std::endl;

    if (!fs::exists(gitBaseDir)) {
        fs::create_directories(gitBaseDir);
    }
    commandHandler4.placeGitFile();
}


void secondPage::on_gitAddButton_clicked()
{

    CommandHandler commandHandler5(chosenDirectory.toStdString());
    if (!commandHandler5.checkGitFile()) {
        std::cerr << "git.txt not found or invalid in the current directory." << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(commandHandler5.currentDirectory)) {
        if (entry.is_regular_file()) {
            commandHandler5.stagedFiles.push_back(entry.path().string());
        }
    }

    for (const auto& elem: commandHandler5.stagedFiles) {
        localStagedFiles.push_back(elem);
    }

    QMessageBox::information(this, "Files added", "Staged files for commit");

}


void secondPage::on_gitPullButton_clicked()
{

}


void secondPage::on_gitCommitButton_clicked()
{

    CommandHandler commandHandler6(chosenDirectory.toStdString());
    if (!commandHandler6.checkGitFile()) {
        std::cerr << "git.txt not found or invalid in the current directory." << std::endl;
        return;
    }

    fs::path gitBaseDir = fs::path("gitBase") / fs::path(commandHandler6.currentDirectory.string()).filename();
    if (!fs::exists(gitBaseDir)) {
        fs::create_directories(gitBaseDir);
    }

    std::string versionDirName = commandHandler6.getVersionDirectoryName();
    fs::path versionDir = gitBaseDir / versionDirName;
    fs::create_directory(versionDir);

    std::string message = ui->commitMessageTextEdit->toPlainText().toStdString();

    std::ostringstream commitInfo;
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    commitInfo << "\n" <<  std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "\n";
    commitInfo << "Message: " << message << "\nFiles:\n";

    for (const auto& file : localStagedFiles) {
        if (fs::path(file).filename() != "git.txt") {
            std::string destFile = versionDir.string() + "/"+ fs::path(file).filename().string();
            fs::copy(file, destFile, fs::copy_options::overwrite_existing);
            commitInfo << fs::path(file).filename() << "\n";
        }
    }

    std::string contentFile = commandHandler6.rewriteGitFileWithNewInfo(commandHandler6.currentDirectory.string() + "/"+ "git.txt",commitInfo.str());


}


void secondPage::on_revertButton_clicked()
{

}

