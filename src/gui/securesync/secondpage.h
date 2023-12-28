#ifndef SECONDPAGE_H
#define SECONDPAGE_H

#include <QDialog>

namespace Ui {
class secondPage;
}

class secondPage : public QDialog
{
    Q_OBJECT

public:
    explicit secondPage(QWidget *parent = nullptr);
    ~secondPage();

private slots:
    void on_chooseDirectoryButton_clicked();

    void on_gitInitButton_clicked();

    void on_gitAddButton_clicked();

    void on_gitPullButton_clicked();

    void on_gitCommitButton_clicked();

    void updateFileList(const QString &directoryPath);

    void on_revertButton_clicked();

private:
    Ui::secondPage *ui;
};

#endif // SECONDPAGE_H
