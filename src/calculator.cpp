#include "calculator.h"
#include "commandhandeling.h"
#include "digitshandling.h"
#include "equalbutton.h"
#include "clearbutton.h"
#include "backspacebutton.h"
#include <QPushButton>
#include <QRegularExpression>


calculator::calculator(QWidget *parent) : QWidget(parent), ui(new Ui::calculator), _currentInput("0")
{
    ui->setupUi(this);

    auto connectDigit = [this](QPushButton* btn) {
        connect(btn, &QPushButton::released, [this, btn]() {
            handleDigitPress(btn->text());
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
    connectDigit(ui->pushBtn_FloatingPoint);

    auto connectOperation = [this](QPushButton* btn) {
        connect(btn, &QPushButton::released, [this, btn]() {
            handleOperationPress(btn->text());
        });
    };

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
