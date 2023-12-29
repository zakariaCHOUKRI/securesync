#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../../CommandHandler.cpp"
#include <QMessageBox>
#include <iostream>
#include "../../test.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_register_button_clicked()
{
    QString username = ui->reg_uname_input->text();
    QString pw1 = ui->reg_pw1_input->text();
    QString pw2 = ui->reg_pw2_input->text();

    std::filesystem::path currentPath = std::filesystem::absolute(std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path());
    CommandHandler commandHandler(currentPath.string());

    // std::string a = currentPath.string();
    // QString qstr = QString::fromStdString(a);

    // QMessageBox::information(this, "Register", qstr);

    std::cout << commandHandler.currentDirectory.string() << std::endl;

    // hadshi rah makhdamsh wa9ila moshkil flpath ola shi l3ba
    if (pw1 == pw2) {

        std::cout << "it is open" << std::endl;
        std::ofstream accountsFile("accounts.txt", std::ios::app);
        std::string hashedPassword = commandHandler.hashPassword(pw1.toStdString());
        accountsFile << username.toStdString() << " " << hashedPassword << std::endl;
        accountsFile.close();
        std::cout << "now closed" << std::endl;

        QMessageBox::information(this, "Register", "Successfully Registered");
    } else {
        QMessageBox::warning(this, "Register", "Passwords do not match");
    }
}

void MainWindow::on_login_button_clicked()
{
    QString username = ui->login_uname_input->text();
    QString pw = ui->login_pw_input->text();

    // hna handli login logic

    std::filesystem::path currentPath3 = std::filesystem::absolute(std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path());
    CommandHandler commandHandler3(currentPath3.string());

    commandHandler3.handleLogin(username.toStdString(), pw.toStdString());
    if (commandHandler3.isLoggedIn == true) {
        hide(); // had line zdtha bash t7yd had lwindow d login o t7l lakhra
        secondpage = new secondPage(this);
        secondpage->show();
    } else {
        QMessageBox::warning(this, "Login", "Incorrect credentials");
    }


}

