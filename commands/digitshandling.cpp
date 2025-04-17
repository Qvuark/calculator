#include "digitshandling.h"
#include "calculator.h"

DigitCommand::DigitCommand(calculator* calc, const QString& digit)
    : _calc(calc), _digit(digit),
    _prevInput(calc->currentInput()),
    _prevExpression(calc->expressionBuffer()) {}

void DigitCommand::execute()
{
    QString current = _calc->currentInput();
    _prevInput = current;
    if(current == "0" && _digit != "0") current.clear();
    if(current.contains('.') && _digit == ".") return;
    current += _digit;
    _calc->setCurrentInput(current);
}

void DigitCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
