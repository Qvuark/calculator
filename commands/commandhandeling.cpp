#include "commandhandeling.h"
#include "calculator.h"

OperationCommand::OperationCommand(calculator* calc, const QString& op) : _calc(calc), _operation(op),
    _prevInput(calc->currentInput()),
    _prevExpression(calc->expressionBuffer()) {}

void OperationCommand::execute()
{

    QString expression = _prevExpression + _prevInput + _operation;
    _calc->setExpressionBuffer(expression);
    _calc->setCurrentInput("");
}

void OperationCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
