#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QByteArray>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDesktopServices>
#include <mergebinarydata.h>
#include <binarytohexstring.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_CreatMerge_clicked();

    void on_pushButton_OpenBoot_clicked();

    void on_pushButton_OpenApp_clicked();

    void on_pushButton_OpenFolder_clicked();

    void on_pushButton_ClearMerge_clicked();

private:
    Ui::MainWindow *ui;
    QString boot_file_name;
    QString app_file_name;
};

#endif // MAINWINDOW_H
