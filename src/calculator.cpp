#include "calculator.h"
#include "command.h"
#include "ui_calculator.h"

#include <QPushButton>
#include <QDebug>
#include <QRegularExpression>


calculator::calculator(QWidget *parent) : QWidget(parent), ui(new Ui::calculator), currentInput("0")
{
    ui->setupUi(this);
    auto connectDigit = [this](QPushButton* btn) {
        connect(btn, &QPushButton::released, [this, btn]() {
            handleDigitPress(btn->text());
        });
    };
    auto connectOperation = [this](QPushButton* btn) {
        connect(btn, &QPushButton::released, [this, btn]() {
            handleOperationPress(btn->text());
        });
    };

    connectDigit(ui->pushBtn_0);
    connectDigit(ui->pushBtn_1);
    connectDigit(ui->pushBtn_2);
    connectDigit(ui->pushBtn_3);
    connectDigit(ui->pushBtn_4);
    connectDigit(ui->pushBtn_5);
    connectDigit(ui->pushBtn_6);
    connectDigit(ui->pushBtn_7);
    connectDigit(ui->pushBtn_8);
    connectDigit(ui->pushBtn_9);

    connectOperation(ui->pushBtn_Add);
    connectOperation(ui->pushBtn_Sub);
    connectOperation(ui->pushBtn_Mult);
    connectOperation(ui->pushBtn_Div);

    setStyleSheet("background-color: white;");
    updateDisplay();
}

calculator::~calculator()
{
    delete ui;
}

void calculator::executeCommand(std::unique_ptr<command> cmd)
{
    // Выполняем команду
    cmd -> execute();
    // Кладём её в undoStack
    undoStack.push_back(std::move(cmd));
    // Очищаем redoStack, т.к. пошли новые действия
    redoStack.clear();
}

void calculator::undoCommand()
{
    if(!undoStack.empty()) {
        auto cmd = std::move(undoStack.back());
        undoStack.pop_back();
        // Вызываем метод undo
        cmd -> undo();
        // Перемещаем команду в redoStack
        redoStack.push_back(std::move(cmd));
    }
}

void calculator::redoCommand()
{
    if(!redoStack.empty()) {
        auto cmd = std::move(redoStack.back());
        redoStack.pop_back();
        // Выполняем команду снова
        cmd->execute();
        // Возвращаем команду в undoStack
        undoStack.push_back(std::move(cmd));
    }
}

QString calculator::getCurrentInput() const
{
    return currentInput;
}
void calculator::setCurrentInput(const QString &input)
{
    currentInput = input;
}
void calculator::updateDisplay()
{
    ui->screen->setText(currentInput);
}
void calculator::handleOperationPress(const QString &sign)
{
    QChar lastChar = currentInput.back();
    if (lastChar == '+' || lastChar == '-' ||
        lastChar == '*' || lastChar == '/')
    {
        currentInput.chop(1);
    }
    expressionBuffer = currentInput + sign;
    currentInput = "";
    updateDisplay();
}
void calculator::handleDigitPress(const QString &digit)
{
    if(currentInput.length() >= 15) return;
    if(currentInput.contains("."))
    {
        QStringList parts = currentInput.split(".");
        if(parts.size() > 1 && parts[1].length() >= 10) return;
    }
    else
    {
        if(currentInput == "0" && digit != "0") { currentInput.clear(); }
        else if(currentInput == "0" && digit == "0") {return;}
    }
    currentInput += digit;
    updateDisplay();
}

void calculator::on_pushBtn_FloatingPoint_released()
{
    if(currentInput.isEmpty() || currentInput.endsWith("+") ||
        currentInput.endsWith("-") || currentInput.endsWith("*") ||
        currentInput.endsWith("/") || currentInput.endsWith(".")) {
        currentInput += "0.";
    }
    else {currentInput += ".";}

    updateDisplay();
}

void calculator::on_pushBtn_00_released()
{
    if(currentInput.length() >= 14) return;

    if(currentInput == "0") {return;}
    else { currentInput += "00";}

    updateDisplay();
}

void calculator::on_pushBtn_Equals_released()
{
    expressionBuffer+=currentInput;
    QStringList numbersParts = expressionBuffer.split(QRegularExpression("[\\+\\-\\*/]"));
    QStringList operationsParts = expressionBuffer.split(QRegularExpression("[0-9\\.]"));
    QVector<double> numbers;
    for(const auto &number : numbersParts)
    {
        numbers.push_back(number.toDouble());
    }
    QVector<QString> operators;
    for(const QString &operation : operationsParts)
    {
        QString op = operation.trimmed();
        if(!op.isEmpty()) operators.push_back(op);
    }
    double result = numbers[0];
    for(int i = 0; i<operators.size() && i<numbers.size()-1;i++)
    {
        QString op = operators[i];
        double nextNumber = numbers[i+1];
        if(op=="+") result+=nextNumber;
        else if(op=="-") result-=nextNumber;
        else if(op=="/") result/=nextNumber;
        else if(op=="*") result*=nextNumber;
    }
    expressionBuffer = QString::number(result);
    currentInput = "";
    updateDisplay();
}

void calculator::on_pushBtn_Backspace_released()
{
    if(currentInput != "0")
    {
        currentInput.chop(1);
    }
    updateDisplay();
}
void calculator::on_pushBtn_Clear_released()
{
    expressionBuffer = "";
    currentInput = "0";
    updateDisplay();
}


void calculator::on_pushBtn_Undo_released()
{
    if(expressionBuffer == "") { currentInput = "0"; }
    else currentInput = "";
    updateDisplay();
}


void calculator::on_pushBtn_Menu_released()
{

}
void calculator::on_pushBtn_Redo_released()
{

}

