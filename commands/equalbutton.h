#ifndef EQUALSCOMMAND_H
#define EQUALSCOMMAND_H

#include "command.h"
#include "calculator.h"

class EqualsCommand : public Command
{
public:
    EqualsCommand(calculator* calc);
    void execute() override;
    void undo() override;

private:
    calculator* _calc;
    QString _prevInput;
    QString _prevExpression;
    double _result;
};

#endif // EQUALSCOMMAND_H
