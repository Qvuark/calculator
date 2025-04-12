#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <memory>
#include <vector>
#include "ui_calculator.h"

class command;

class calculator : public QWidget
{
    Q_OBJECT
public:
    explicit calculator(QWidget *parent = nullptr);
    ~calculator();

    void executeCommand(std::unique_ptr<command> cmd);
    void undoCommand();
    void redoCommand();

    QString getCurrentInput() const;
    void setCurrentInput(const QString &input);
    void addDigit(const QString &digit);
    void updateDisplay();

private slots:
    void handleDigitPress(const QString &digit);
    void handleOperationPress(const QString &digit);
    void on_pushBtn_FloatingPoint_released();
    void on_pushBtn_00_released();
    void on_pushBtn_Equals_released();

    void on_pushBtn_Backspace_released();
    void on_pushBtn_Clear_released();
    void on_pushBtn_Redo_released();
    void on_pushBtn_Undo_released();

    void on_pushBtn_Menu_released();
private:
    Ui::calculator *ui;
    QString currentInput;
    QString expressionBuffer;

    std::vector<std::unique_ptr<command>> undoStack;
    std::vector<std::unique_ptr<command>> redoStack;
};

#endif // CALCULATOR_H
