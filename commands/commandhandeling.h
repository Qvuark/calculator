#ifndef OPERATIONCOMMAND_H
#define OPERATIONCOMMAND_H

#include "command.h"
#include <QString>

class calculator;

class OperationCommand : public Command
{
public:
    OperationCommand(calculator* calc, const QString& operation);
    void execute() override;
    void undo() override;

private:
    calculator* _calc;
    QString _operation;
    QString _prevInput;
    QString _prevExpression;
};

#endif // OPERATIONCOMMAND_H
