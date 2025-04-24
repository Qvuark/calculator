#include "calculator.h"
#include "commandhandeling.h"
#include "digitshandling.h"
#include "equalbutton.h"
#include "clearbutton.h"
#include "backspacebutton.h"
#include "functionshandeling.h"
#include <QPushButton>
#include <QRegularExpression>


calculator::calculator(QWidget *parent) : QWidget(parent), ui(new Ui::calculator), _currentInput("0")
{
    ui->setupUi(this);

    const QStringList digitTokens = {"0","1","2","3","4","5","6","7","8","9","00",".","pi","e"};
    auto buttons = this->findChildren<QPushButton*>();
    for (auto *btn : buttons)
    {
        QString txt = btn->text();
        if (digitTokens.contains(txt))
        {
            connect(btn, &QPushButton::released, this, [this, btn]() {
                handleDigitPress(btn->text());
            });
        }
    }
    const QStringList opTokens = {"+","-","*","/"};
    for (auto *btn : buttons)
    {
        QString txt = btn->text();
        if (opTokens.contains(txt))
        {
            connect(btn, &QPushButton::released, this, [this, btn]() {
                handleOperationPress(btn->text());
            });
        }
    }
    const QStringList fcTokens = {"√","^","ln"};
    for (auto *btn : buttons)
    {
        QString txt = btn->text();
        if (fcTokens.contains(txt))
        {
            connect(btn, &QPushButton::released, this, [this, btn]() {
                handleFuncPress(btn->text());
            });
        }
    }
    for(auto *btn : buttons)
    {
        QString txt = btn->text();
        if(txt.contains("="))
        {
            connect(btn, &QPushButton::released, this, &calculator::on_pushBtn_Equals_released);
        }
        else if(txt.contains("⌫"))
        {
            connect(btn, &QPushButton::released, this, &calculator::on_pushBtn_Backspace_released);
        }
        else if(txt.contains("C"))
        {
            connect(btn, &QPushButton::released, this, &calculator::on_pushBtn_Clear_released);
        }
        else if(txt.contains("REDO"))
        {
            connect(btn, &QPushButton::released, this, &calculator::on_pushBtn_Redo_released);
        }
        else if(txt.contains("UNDO"))
        {
            connect(btn, &QPushButton::released, this, &calculator::on_pushBtn_Undo_released);
        }
    }


    setStyleSheet("background-color: white;");
    updateDisplay();
}

calculator::~calculator()
{
    delete ui;
}

void calculator::executeCommand(std::unique_ptr<Command> cmd)
{
    cmd->execute();

    if (undoStack.size() >= MAX_HISTORY_BUFFER)
    {
        undoStack.erase(undoStack.begin());
    }

    undoStack.push_back(std::move(cmd));

    redoStack.clear();

    qDebug() << "Command executed. Undo stack size:" << undoStack.size();

    updateDisplay();
}
void calculator::undoCommand()
{
    if(!undoStack.empty())
    {
        auto cmd = std::move(undoStack.back());
        undoStack.pop_back();
        cmd->undo();
        redoStack.push_back(std::move(cmd));
        updateDisplay();
    }
}

void calculator::redoCommand()
{
    if(!redoStack.empty())
    {
        auto cmd = std::move(redoStack.back());
        redoStack.pop_back();
        cmd->execute();
        undoStack.push_back(std::move(cmd));
        updateDisplay();
    }
}

void calculator::handleDigitPress(const QString &digit)
{
    executeCommand(std::make_unique<DigitCommand>(this, digit));
}
void calculator::handleOperationPress(const QString &operation)
{
    executeCommand(std::make_unique<OperationCommand>(this, operation));
}
void calculator::handleFuncPress(const QString &func)
{
    executeCommand(std::make_unique<FuncCommand>(this, func));
}
void calculator::on_pushBtn_Equals_released()
{
    executeCommand(std::make_unique<EqualsCommand>(this));
}
void calculator::on_pushBtn_Clear_released()
{
    executeCommand(std::make_unique<ClearCommand>(this));
}
void calculator::on_pushBtn_Backspace_released()
{
    executeCommand(std::make_unique<BackspaceCommand>(this));
}
void calculator::on_pushBtn_Undo_released()
{
    undoCommand();
}
void calculator::on_pushBtn_Redo_released()
{
    redoCommand();
}

QString calculator::currentInput() const { return _currentInput; }

QString calculator::expressionBuffer() const { return _expressionBuffer; }

void calculator::setCurrentInput(const QString &input) { _currentInput = input; }

void calculator::setExpressionBuffer(const QString &expression) { _expressionBuffer = expression; }

void calculator::updateDisplay()
{
    QString display = _expressionBuffer;
    if(!_currentInput.isEmpty()) { display += _currentInput; }
    ui->screen->setText(display);
}

void calculator::on_pushBtn_Menu_released()
{
    int idx = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(idx == 0 ? 1 : 0);
}


