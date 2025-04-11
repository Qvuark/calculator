#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "ui_calculator.h"

class calculator : public QWidget
{
    Q_OBJECT
public:
    explicit calculator(QWidget *parent = nullptr);
    ~calculator();

private slots:
    void handleDigitPress(const QString &digit);
    void handleOperationPress(const QString &digit);
    void on_pushBtn_FloatingPoint_released();
    void on_pushBtn_00_released();
    void on_pushBtn_Backspace_released();
    void on_pushBtn_Equals_released();

    void on_pushBtn_Clear_released();

    void on_pushBtn_Clear_Entry_released();

private:
    Ui::calculator *ui;
    QString expressionBuffer;
    QString currentInput;
    void updateDisplay();
};

#endif // CALCULATOR_H
