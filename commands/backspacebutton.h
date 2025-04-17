#ifndef BACKSPACECOMMAND_H
#define BACKSPACECOMMAND_H

#include "command.h"
#include "calculator.h"

class BackspaceCommand : public Command
{
public:
    BackspaceCommand(calculator* calc);
    void execute() override;
    void undo() override;

private:
    calculator* _calc;
    QString _prevInput;
    QString _prevExpression;
};

#endif // BACKSPACECOMMAND_H
