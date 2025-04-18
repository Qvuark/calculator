#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <memory>
#include <vector>
#include "ui_calculator.h"
#include "command.h"

class calculator : public QWidget
{
    Q_OBJECT
public:
    explicit calculator(QWidget *parent = nullptr);
    ~calculator();

    QString currentInput() const;
    QString expressionBuffer() const;
    void setCurrentInput(const QString &input);
    void setExpressionBuffer(const QString &expression);

    void executeCommand(std::unique_ptr<Command> cmd);
    void undoCommand();
    void redoCommand();

private slots:
    void handleDigitPress(const QString &digit);
    void handleOperationPress(const QString &operation);
    void handleFuncPress(const QString &func);
    void on_pushBtn_Equals_released();
    void on_pushBtn_Clear_released();
    void on_pushBtn_Backspace_released();
    void on_pushBtn_Undo_released();
    void on_pushBtn_Redo_released();
    void on_pushBtn_Menu_released();

private:
    Ui::calculator *ui;
    QString _currentInput;
    QString _expressionBuffer;
    std::vector<std::unique_ptr<Command>> undoStack;
    std::vector<std::unique_ptr<Command>> redoStack;
    const int MAX_HISTORY_BUFFER = 100;

    void updateDisplay();
};

#endif // CALCULATOR_H
