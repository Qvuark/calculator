#include "backspacebutton.h"

BackspaceCommand::BackspaceCommand(calculator* calc)
    : _calc(calc),
    _prevInput(calc->currentInput()),
    _prevExpression(calc->expressionBuffer()) {}

void BackspaceCommand::execute()
{
    QString cur = _calc->currentInput();
    QString expr = _calc->expressionBuffer();
    if (!cur.isEmpty())
    {
        cur.chop(1);
        _calc->setCurrentInput(cur);
    }
    else if (!expr.isEmpty())
    {
        expr.chop(1);
        _calc->setExpressionBuffer(expr);
    }
}
void BackspaceCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
