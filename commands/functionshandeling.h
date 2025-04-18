#ifndef FUNCCOMMAND_H
#define FUNCCOMMAND_H

#include "command.h"
#include <QString>

class calculator;

class FuncCommand : public Command
{
public:
    FuncCommand(calculator* calc, const QString& operation);
    void execute() override;
    void undo() override;

private:
    calculator* _calc;
    QString _operation;
    QString _prevInput;
    QString _prevExpression;
};

#endif // OPERATIONCOMMAND_H
