#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    double mounth=1;//кол-во месяцев
    double percent=1;//процент
    double money=1;//кол-во денег
    double A;//Коэф аннуитетного кредита
    double P;//Аннуитетный кредит процент
    double Na;//Платеж в месяц
    double osn;//Остаток по основному долгу
    double percent_m;//проценты в месяц
    double ost;//остаток по кредиту
    double itog;//итоговая сумма при аннуитетном кредите
    double itog_dif;//итоговая сумма при дифференцированном кредите
    double pereplata;//переплата по кредиту

    Ui::MainWindow *ui;
    void anuit();//вычисление аннуитетного
    void dif();//вычисление дифференцированного
    void set();//установка значений
private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_pushButton_2_clicked();
    void on_doubleSpinBox_valueChanged(double arg1);
};
#endif // MAINWINDOW_H
