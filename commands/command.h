#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

class calculator;

class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

#endif // COMMAND_H
