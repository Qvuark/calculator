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

    if (_digit == "pi")
    {
        _calc->setCurrentInput(current + "3.14");
        return;
    }
    else if(_digit == "e")
    {
        _calc->setCurrentInput(current + "2.71");
        return;
    }

    current += _digit;
    _calc->setCurrentInput(current);
}


void DigitCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
