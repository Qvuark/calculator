#include "equalbutton.h"
#include "calculator.h"
#include <QRegularExpression>

EqualsCommand::EqualsCommand(calculator* calc)
    : _calc(calc),
    _prevInput(calc->currentInput()),
    _prevExpression(calc->expressionBuffer()) {}

void EqualsCommand::execute()
{
    QString fullExpression = _prevExpression + _prevInput;

    QRegularExpression re(R"(([+\-*/])|([0-9]+\.?[0-9]*))");
    QRegularExpressionMatchIterator i = re.globalMatch(fullExpression);

    QVector<double> numbers;
    QVector<QString> operations;

    while(i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        QString token = match.captured(0);

        if(token.isEmpty()) continue;
        if(token == "+" || token == "-" || token == "*" || token == "/")
        {
            operations.push_back(token);
        }
        else
        {
            bool ok;
            double num = token.toDouble(&ok);
            if(ok) numbers.push_back(num);
        }
    }
    if(numbers.size() > 0)
    {
        _result = numbers[0];
        for(int i = 0; i < operations.size() && i < numbers.size()-1; i++)
        {
            double next = numbers[i+1];

            if(operations[i] == "+") _result += next;
            else if(operations[i] == "-") _result -= next;
            else if(operations[i] == "*") _result *= next;
            else if(operations[i] == "/" && next != 0.0) _result /= next;
            else qDebug() <<"U cant divide by zero, silly";
        }

        QString resultStr = QString::number(_result, 'f', 2);
        if(resultStr.endsWith(".00"))
        {
            resultStr.chop(3);
        }
        else if(resultStr.endsWith("0") && resultStr.contains('.'))
        {
            resultStr.chop(1);
        }
        _calc->setExpressionBuffer(resultStr);
        _calc->setCurrentInput("");
    }
}

void EqualsCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
