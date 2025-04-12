#include "digitshandling.h"
#include "../src/calculator.h"

digitsHandling::digitsHandling(calculator *calc, const QString &digit) : _calc(calc), _digit(digit) {}

void digitsHandling::execute()
{
    _prevInput = _calc -> getCurrentInput();
    _calc->updateDisplay();
}

void digitsHandling::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->updateDisplay();
}
