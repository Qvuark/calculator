#include "functionshandeling.h"
#include "calculator.h"

FuncCommand::FuncCommand(calculator* calc, const QString& op) : _calc(calc), _operation(op),
    _prevInput(calc->currentInput()),
    _prevExpression(calc->expressionBuffer()) {}

void FuncCommand::execute()
{
    QString expression = _prevExpression + _prevInput + _operation;
    _calc->setExpressionBuffer(expression);
    _calc->setCurrentInput("");
}
void FuncCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
