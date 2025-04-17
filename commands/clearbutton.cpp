#include "clearbutton.h"

ClearCommand::ClearCommand(calculator* calc)
    : _calc(calc),
    _prevInput(calc->currentInput()),
    _prevExpression(calc->expressionBuffer()) {}

void ClearCommand::execute()
{
    _calc->setCurrentInput("0");
    _calc->setExpressionBuffer("");
}

void ClearCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
