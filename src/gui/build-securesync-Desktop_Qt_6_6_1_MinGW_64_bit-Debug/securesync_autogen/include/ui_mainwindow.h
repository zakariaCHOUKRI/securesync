/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *username_register;
    QLabel *pw1_register;
    QLabel *pw2_register;
    QLineEdit *reg_uname_input;
    QLineEdit *reg_pw1_input;
    QLineEdit *reg_pw2_input;
    QPushButton *register_button;
    QGroupBox *groupBox_2;
    QLabel *username_login;
    QLabel *pw1_login;
    QLineEdit *login_uname_input;
    QLineEdit *login_pw_input;
    QPushButton *login_button;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(846, 448);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 120, 361, 251));
        QFont font;
        font.setPointSize(24);
        groupBox->setFont(font);
        username_register = new QLabel(groupBox);
        username_register->setObjectName("username_register");
        username_register->setGeometry(QRect(10, 50, 101, 41));
        QFont font1;
        font1.setPointSize(14);
        username_register->setFont(font1);
        pw1_register = new QLabel(groupBox);
        pw1_register->setObjectName("pw1_register");
        pw1_register->setGeometry(QRect(10, 100, 101, 41));
        pw1_register->setFont(font1);
        pw2_register = new QLabel(groupBox);
        pw2_register->setObjectName("pw2_register");
        pw2_register->setGeometry(QRect(10, 150, 161, 41));
        pw2_register->setFont(font1);
        reg_uname_input = new QLineEdit(groupBox);
        reg_uname_input->setObjectName("reg_uname_input");
        reg_uname_input->setGeometry(QRect(170, 60, 181, 24));
        reg_uname_input->setFont(font1);
        reg_pw1_input = new QLineEdit(groupBox);
        reg_pw1_input->setObjectName("reg_pw1_input");
        reg_pw1_input->setGeometry(QRect(170, 110, 181, 24));
        reg_pw1_input->setFont(font1);
        reg_pw2_input = new QLineEdit(groupBox);
        reg_pw2_input->setObjectName("reg_pw2_input");
        reg_pw2_input->setGeometry(QRect(170, 160, 181, 24));
        reg_pw2_input->setFont(font1);
        register_button = new QPushButton(groupBox);
        register_button->setObjectName("register_button");
        register_button->setGeometry(QRect(120, 200, 91, 31));
        QFont font2;
        font2.setPointSize(12);
        register_button->setFont(font2);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(450, 120, 361, 251));
        groupBox_2->setFont(font);
        username_login = new QLabel(groupBox_2);
        username_login->setObjectName("username_login");
        username_login->setGeometry(QRect(10, 50, 101, 41));
        username_login->setFont(font1);
        pw1_login = new QLabel(groupBox_2);
        pw1_login->setObjectName("pw1_login");
        pw1_login->setGeometry(QRect(10, 100, 101, 41));
        pw1_login->setFont(font1);
        login_uname_input = new QLineEdit(groupBox_2);
        login_uname_input->setObjectName("login_uname_input");
        login_uname_input->setGeometry(QRect(170, 60, 181, 24));
        login_uname_input->setFont(font1);
        login_pw_input = new QLineEdit(groupBox_2);
        login_pw_input->setObjectName("login_pw_input");
        login_pw_input->setGeometry(QRect(170, 110, 181, 24));
        login_pw_input->setFont(font1);
        login_button = new QPushButton(groupBox_2);
        login_button->setObjectName("login_button");
        login_button->setGeometry(QRect(120, 200, 91, 31));
        login_button->setFont(font2);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(230, 40, 351, 61));
        label->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 846, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SecureSync GUI", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Register", nullptr));
        username_register->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        pw1_register->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        pw2_register->setText(QCoreApplication::translate("MainWindow", "Confirm password", nullptr));
        register_button->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Login", nullptr));
        username_login->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        pw1_login->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        login_button->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Welcome to SecureSync", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
