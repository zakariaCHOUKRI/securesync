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

static unsigned int localVersionNumber;

static CommandHandler ch("");

static std::filesystem::path rootDirectory = std::filesystem::absolute(std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path());

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

        ch.currentDirectory = chosenDirectory.toStdString();
        ch.isLoggedIn = true;
        std::cout << ch.currentDirectory << std::endl;

        if (ch.checkGitFile()) {
            ui->gitInitButton->setEnabled(false);
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

    // std::cout << gitBase << std::endl;

    fs::path gitBaseDir = fs::path("gitBase") / fs::path(ch.currentDirectory.string()).filename();
    // std::cout << gitBaseDir << std::endl;

    if (!fs::exists(gitBaseDir)) {
        fs::create_directories(gitBaseDir);
    }
    ch.placeGitFile();

    updateFileList(chosenDirectory);
}


void secondPage::on_gitAddButton_clicked()
{

    ch.handleAdd(".");
    updateFileList(chosenDirectory);
    QMessageBox::information(this, "Files added", "Staged files for commit");

}


void secondPage::on_gitPullButton_clicked()
{

    ch.handlePull();
    updateFileList(chosenDirectory);
    QMessageBox::information(this, "Pull", "Files restored to their latest version");

}


void secondPage::on_gitCommitButton_clicked()
{

    std::string message = ui->commitMessageTextEdit->toPlainText().toStdString();
    ch.handleCommit(message);
    updateFileList(chosenDirectory);
    QMessageBox::information(this, "Files Commited", "Commit successful");

}


void secondPage::on_revertButton_clicked()
{

    unsigned int vers = std::stoul(ui->revertInput->text().toStdString());
    ch.handleRevert(vers);
    updateFileList(chosenDirectory);
    QMessageBox::information(this, "Revert", "Reverted to wanted version");

}

