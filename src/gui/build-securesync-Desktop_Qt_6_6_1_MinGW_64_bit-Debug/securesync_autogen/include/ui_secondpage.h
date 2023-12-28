/********************************************************************************
** Form generated from reading UI file 'secondpage.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDPAGE_H
#define UI_SECONDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_secondPage
{
public:
    QLineEdit *directoryLineEdit;
    QPushButton *chooseDirectoryButton;
    QListWidget *fileListWidget;
    QPushButton *gitInitButton;
    QPushButton *gitAddButton;
    QPushButton *gitPullButton;
    QPushButton *gitCommitButton;
    QTextEdit *commitMessageTextEdit;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *secondPage)
    {
        if (secondPage->objectName().isEmpty())
            secondPage->setObjectName("secondPage");
        secondPage->resize(844, 379);
        directoryLineEdit = new QLineEdit(secondPage);
        directoryLineEdit->setObjectName("directoryLineEdit");
        directoryLineEdit->setGeometry(QRect(140, 20, 401, 25));
        chooseDirectoryButton = new QPushButton(secondPage);
        chooseDirectoryButton->setObjectName("chooseDirectoryButton");
        chooseDirectoryButton->setGeometry(QRect(20, 20, 111, 23));
        fileListWidget = new QListWidget(secondPage);
        fileListWidget->setObjectName("fileListWidget");
        fileListWidget->setGeometry(QRect(560, 40, 271, 321));
        gitInitButton = new QPushButton(secondPage);
        gitInitButton->setObjectName("gitInitButton");
        gitInitButton->setGeometry(QRect(20, 70, 75, 30));
        gitAddButton = new QPushButton(secondPage);
        gitAddButton->setObjectName("gitAddButton");
        gitAddButton->setGeometry(QRect(20, 110, 75, 30));
        gitPullButton = new QPushButton(secondPage);
        gitPullButton->setObjectName("gitPullButton");
        gitPullButton->setGeometry(QRect(20, 150, 75, 30));
        gitCommitButton = new QPushButton(secondPage);
        gitCommitButton->setObjectName("gitCommitButton");
        gitCommitButton->setGeometry(QRect(20, 330, 75, 30));
        commitMessageTextEdit = new QTextEdit(secondPage);
        commitMessageTextEdit->setObjectName("commitMessageTextEdit");
        commitMessageTextEdit->setGeometry(QRect(110, 90, 431, 271));
        label = new QLabel(secondPage);
        label->setObjectName("label");
        label->setGeometry(QRect(630, 20, 131, 16));
        label_2 = new QLabel(secondPage);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 70, 131, 16));

        retranslateUi(secondPage);

        QMetaObject::connectSlotsByName(secondPage);
    } // setupUi

    void retranslateUi(QDialog *secondPage)
    {
        secondPage->setWindowTitle(QCoreApplication::translate("secondPage", "SecureSync GUI", nullptr));
        chooseDirectoryButton->setText(QCoreApplication::translate("secondPage", "Choose directory", nullptr));
        gitInitButton->setText(QCoreApplication::translate("secondPage", "git init", nullptr));
        gitAddButton->setText(QCoreApplication::translate("secondPage", "git add", nullptr));
        gitPullButton->setText(QCoreApplication::translate("secondPage", "git pull", nullptr));
        gitCommitButton->setText(QCoreApplication::translate("secondPage", "git commit", nullptr));
        label->setText(QCoreApplication::translate("secondPage", "content of the directory ", nullptr));
        label_2->setText(QCoreApplication::translate("secondPage", "commit message", nullptr));
    } // retranslateUi

};

namespace Ui {
    class secondPage: public Ui_secondPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDPAGE_H
