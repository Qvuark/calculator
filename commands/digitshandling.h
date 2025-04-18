#ifndef DIGITSCOMMAND_H
#define DIGITSCOMMAND_H

#include "command.h"
#include <QString>

class calculator;

class DigitCommand : public Command
{
public:
    DigitCommand(calculator* calc, const QString& digit);
    void execute() override;
    void undo() override;
private:
    calculator* _calc;
    QString _digit;
    QString _prevInput;
    QString _prevExpression;
};

#endif // DIGITSCOMMAND_H
