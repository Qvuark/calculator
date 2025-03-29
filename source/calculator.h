#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "ui_calculator.h"

class calculator : public QWidget
{
    Q_OBJECT
public:
    calculator(QWidget *parent = nullptr);
    ~calculator();

private slots:
    void handleButtonClick();

private:
    Ui::calculator *ui;
};

#endif // CALCULATOR_H
