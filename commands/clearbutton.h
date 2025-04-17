#ifndef CLEARCOMMAND_H
#define CLEARCOMMAND_H

#include "command.h"
#include "calculator.h"

class ClearCommand : public Command
{
public:
    ClearCommand(calculator* calc);
    void execute() override;
    void undo() override;

private:
    calculator* _calc;
    QString _prevInput;
    QString _prevExpression;
};

#endif // CLEARCOMMAND_H
