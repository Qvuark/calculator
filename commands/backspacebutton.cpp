#include "backspacebutton.h"

BackspaceCommand::BackspaceCommand(calculator* calc)
    : _calc(calc),
    _prevInput(calc->currentInput()),
    _prevExpression(calc->expressionBuffer()) {}

void BackspaceCommand::execute()
{
    QString current = _prevInput;
    if(current.length() > 1)
    {
        _calc->setCurrentInput(current.chopped(1));
    }
    else
    {
        _calc->setCurrentInput("0");
    }
}
void BackspaceCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
