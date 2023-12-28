#include "secondpage.h"
#include "ui_secondpage.h"
#include <qfiledialog.h>
#include "../../../include/CommandHandler.h"
#include <iostream>

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
    QString directory = QFileDialog::getExistingDirectory(this, "Select a Directory");

    if (!directory.isEmpty()) {
        ui->directoryLineEdit->setText(directory);
        updateFileList(directory);

        std::filesystem::path currentPath2 = std::filesystem::absolute(std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path());
        CommandHandler commandHandler2(currentPath2.string());

        commandHandler2.currentDirectory = directory.toStdString();
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

}


void secondPage::on_gitAddButton_clicked()
{

}


void secondPage::on_gitPullButton_clicked()
{

}


void secondPage::on_gitCommitButton_clicked()
{

}

