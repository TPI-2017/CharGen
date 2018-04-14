#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QMessageBox>
#include <fstream>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum type_output {BINARIO, HEX};

private slots:
    void on_saveButton_clicked();

    void on_binarioRadioButton_clicked();

    void on_hexRadioButton_clicked();

    void on_resetButton_clicked();

    void on_clearButton_clicked();

    void dialogIsFinished(int result);

private:
    static const int ROW = 8;
    static const int COL = 8;
    type_output out = BINARIO;
    Ui::MainWindow *ui;
    std::ofstream newFile;
    QCheckBox* vec[ROW][COL];
    std::string nameFile = "output.txt";
    QMessageBox *confirmBox;

    std::string createCharOutput();
    std::string matrixToHex();
    std::string matrixToBinario();
};

#endif // MAINWINDOW_H
