#pragma once
#pragma once
#ifndef FIRSTWIN_H
#define FIRSTWIN_H
#include "process.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class FirstWin; }
QT_END_NAMESPACE

class FirstWin : public QMainWindow
{
    Q_OBJECT

public:
    FirstWin(QWidget *parent = nullptr);
    ~FirstWin();

    void plot();

private slots:

    void on_pushButton_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_4_clicked(bool checked);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

private:
    Ui::FirstWin *ui;
    Equation *signal;
    Equation *impulse;
    Equation *convolution;
    Equation *correlation;

    double up, down, max, min;
    int signalType, impulseType;

};
#endif // FIRSTWIN_H
