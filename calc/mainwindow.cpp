#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtMath>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:#b8c2e3;");
    ui->lineEdit->setValidator(new QIntValidator(0,1000000,this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set(){

    ui->tableWidget->setRowCount(mounth);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"Сумма платежа"<<"Основной долг"<<"Проценты"<<"Остаток");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ost=money;
    P=percent/1200;
    A=P*pow((1+P),mounth)/(pow((1+P),mounth)-1);
    Na=A*money;//сумма ежемесячного платежа
    itog=Na*mounth;
    pereplata=itog-money;
    itog_dif=0;
}
//аннуитетный
void MainWindow::anuit(){
    set();//установка значений
    ui->label_22->setText(QString::number(itog,'g',7));//вывод итоговой суммы кредита
    ui->label_23->setText(QString::number(pereplata,'g',7));//вывод переплаты
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        percent_m=ost*P;//вычисление процента
        osn=Na-percent_m;//вычисление основоного долга
        ost-=osn;//вычисление остатка
        if(ost<=1){
        ost=0;
        }
        QTableWidgetItem* item1 = new QTableWidgetItem;//в месяц
        QTableWidgetItem* item2 = new QTableWidgetItem;//основной долг
        QTableWidgetItem* item3 = new QTableWidgetItem;//процент в месяц
        QTableWidgetItem* item4 = new QTableWidgetItem;//остаток
        QString sum=QString::number(Na,'g',5);
        QString osn1=QString::number(osn,'g',5);
        QString pm=QString::number(percent_m,'g',4);
        QString ost1=QString::number(ost,'g',5);
        item1->setText(sum);
        item2->setText(osn1);
        item3->setText(pm);
        item4->setText(ost1);
        //добавление в таблицу
        ui->tableWidget->setItem(i,0,item1);
        ui->tableWidget->setItem(i,1,item2);
        ui->tableWidget->setItem(i,2,item3);
        ui->tableWidget->setItem(i,3,item4);
    }
}
//дифференцированный
void MainWindow::dif(){
    set();//установка значений
    ui->tableWidget->setRowCount(mounth);
    for(int i=0;i<mounth;i++){
        double telo=money/mounth;//основной долг
        double ostatok=money-(telo*(i));//остаток задолжности
        double proc=ostatok*(percent/1200);//процент в месяц
        double in_mounth=telo+proc;//процент в месяц
       QTableWidgetItem* item1 = new QTableWidgetItem;//в месяц
        QTableWidgetItem* item2 = new QTableWidgetItem;//основной долг
        QTableWidgetItem* item3 = new QTableWidgetItem;//процент в месяц
        QTableWidgetItem* item4 = new QTableWidgetItem;//остаток
        QString in=QString::number(in_mounth,'g',5);
        QString osn1=QString::number(telo,'g',5);
        QString pm=QString::number(proc,'g',4);
        QString ost1=QString::number(ostatok,'g',5);
        item1->setText(in);
        item2->setText(osn1);
        item3->setText(pm);
        item4->setText(ost1);
        //добавление в таблицу
        ui->tableWidget->setItem(i,0,item1);
        ui->tableWidget->setItem(i,1,item2);
        ui->tableWidget->setItem(i,2,item3);
        ui->tableWidget->setItem(i,3,item4);
        itog_dif+=in_mounth;
    }
    pereplata=itog_dif-money;
    ui->label_22->setText(QString::number(itog_dif,'g',7));//вывод итоговой суммы кредита
    ui->label_23->setText(QString::number(pereplata,'g',7));//вывод переплаты
}
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    mounth=arg1;//при изменении==присвоение месяца
}

//выбор вида кредита
void MainWindow::on_pushButton_clicked(){
int i=ui->comboBox->currentIndex();
switch(i){
case 0: anuit();
    break;
case 1: dif();
    break;
}
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    money=arg1.toDouble();//при изменении==присвоение кол-во денег
}


//Вывод справки по видам кредита
void MainWindow::on_pushButton_2_clicked()
{
    int i=ui->comboBox->currentIndex();
    if(i==0){
    QMessageBox msg;
    msg.setWindowTitle("Справка");
    msg.setText("Аннуитетный платеж- метод погашения, при котором размер ссуды делится на равные части,которые клиент стабильно выплачивает");
    msg.exec();
    }
    else{
     QMessageBox msg;
     msg.setWindowTitle("Справка");
   msg.setText("Дифференциальный платеж- метод погашения, при котором заемщик вносит разные суммы, размер которых с каждым разом уменьшается");
   msg.exec();
    }
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    percent=arg1;//при изменении==присвоение кол-во процентов
}

