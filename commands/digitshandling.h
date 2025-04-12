#ifndef DIGITSHANDLING_H
#define DIGITSHANDLING_H

#include <QString>
#include <command.h>

class calculator;

class digitsHandling : public command
{
public:
    digitsHandling(calculator *cals, const QString &digit);
    virtual void execute() override;
    virtual void undo() override;
private:
    calculator *_calc;
    QString _digit;
    QString _prevInput;
};

#endif // DIGITSHANDLING_H
