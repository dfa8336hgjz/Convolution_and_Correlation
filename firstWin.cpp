#include "firstWin.h"
#include "ui_firstWin.h"
#include "QDoubleValidator"

FirstWin::FirstWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FirstWin)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->lineEdit_2->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->lineEdit_3->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->lineEdit_4->setValidator(new QDoubleValidator(-100, 100, 2, this));
    ui->stackedWidget->setCurrentWidget(ui->page);
    signal = nullptr;
    impulse = nullptr;
    convolution = nullptr;
    correlation = nullptr;

    up = down = max = min = 0;
    signalType = impulseType = 0;
}

FirstWin::~FirstWin()
{
    delete ui;
    if(signal) delete signal;
    if(impulse) delete impulse;
    if(convolution) delete convolution;
    if(correlation) delete correlation;
}

void FirstWin::on_pushButton_clicked(bool checked)
{
    if(!checked) {
        ui->stackedWidget->setCurrentWidget(ui->page_2);
    }
}


void FirstWin::on_pushButton_2_clicked(bool checked)
{
    if(!checked){
        if (ui->radioButton->isChecked()){
            ui->stackedWidget_2->setCurrentWidget(ui->page_2_1);
            signalType = 1;
        }
        else if (ui->radioButton_2->isChecked()){
            ui->stackedWidget_2->setCurrentWidget(ui->page_2_2);
            signalType = 2;
        }
        else{
            ui->stackedWidget_2->setCurrentWidget(ui->page_2_3);
            signalType = 3;
        }

        ui->stackedWidget->setCurrentWidget(ui->page_3);

        if (ui->radioButton_4->isChecked()){
            ui->stackedWidget_3->setCurrentWidget(ui->page_2_7);
            impulseType = 1;
        }
        else if (ui->radioButton_5->isChecked()){
            ui->stackedWidget_3->setCurrentWidget(ui->page_2_8);
            impulseType = 2;
        }
        else {
            ui->stackedWidget_3->setCurrentWidget(ui->page_2_9);
            impulseType = 3;
        }

        ui->stackedWidget->setCurrentWidget(ui->page_3);
    }
}


void FirstWin::on_pushButton_3_clicked(bool checked)
{
    if(!checked){
        if (signalType == 1){
            QString a = ui->textEdit->toPlainText();
            signal = new LinearEquation(this->up, this->down, a.toStdString());
        }
        else if (signalType == 2){
            QString a = ui->textEdit_2->toPlainText();
            signal = new ExponentialEquation(this->up, this->down, a.toStdString());
        }
        else{
            QString a = ui->textEdit_4->toPlainText();
            signal = new SinusoidalEquation(this->up, this->down, a.toStdString());
        }
        ui->stackedWidget->setCurrentWidget(ui->page_4);
    }
}


void FirstWin::on_pushButton_4_clicked(bool checked)
{
    if(!checked){
        if (impulseType == 1){
            QString a = ui->textEdit_3->toPlainText();
            impulse = new LinearEquation(this->max, this->min, a.toStdString());
        }
        else if (impulseType == 2){
            QString a = ui->textEdit_6->toPlainText();
            impulse = new ExponentialEquation(this->max, this->min, a.toStdString());
        }
        else{
            QString a = ui->textEdit_5->toPlainText();
            impulse = new SinusoidalEquation(this->max, this->min, a.toStdString());
        }


        convolution = calConvolutional(signal, impulse);
        correlation = calCorrelation(signal, impulse);
        plot();
        ui->stackedWidget->setCurrentWidget(ui->page_5);
    }
}

void FirstWin::on_lineEdit_textChanged(const QString &arg1)
{
    up = arg1.toDouble();
}


void FirstWin::on_lineEdit_3_textChanged(const QString &arg1)
{
    max = arg1.toDouble();
}


void FirstWin::on_lineEdit_2_textChanged(const QString &arg1)
{
    down = arg1.toDouble();
}


void FirstWin::on_lineEdit_4_textChanged(const QString &arg1)
{
    min = arg1.toDouble();
}

void FirstWin::plot(){
    cv::Mat curplot = signal->Plot(391, 181, cv::Scalar(127,170,85));
    QImage curpic((uchar*)curplot.data, curplot.cols, curplot.rows, curplot.step, QImage::Format_BGR888);
    ui->label_17->setPixmap(QPixmap::fromImage(curpic));
    curplot = impulse->Plot(391, 181, cv::Scalar(0,85,255));
    QImage curpic2((uchar*)curplot.data, curplot.cols, curplot.rows, curplot.step, QImage::Format_BGR888);
    ui->label_18->setPixmap(QPixmap::fromImage(curpic2));
    curplot = convolution->Plot(391, 181, cv::Scalar(0,0,255));
    QImage curpic3((uchar*)curplot.data, curplot.cols, curplot.rows, curplot.step, QImage::Format_BGR888);
    ui->label_19->setPixmap(QPixmap::fromImage(curpic3));
    curplot = correlation->Plot(391, 181, cv::Scalar(255,85,85));
    QImage curpic4((uchar*)curplot.data, curplot.cols, curplot.rows, curplot.step, QImage::Format_BGR888);
    ui->label_20->setPixmap(QPixmap::fromImage(curpic4));

    signal->makeStringEquation();
    ui->label_25->setText(QString(signal->equation.c_str()));

    impulse->makeStringEquation();
    ui->label_26->setText(QString(impulse->equation.c_str()));
}
