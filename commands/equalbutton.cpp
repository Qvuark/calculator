#include "equalbutton.h"
#include "calculator.h"
#include <QRegularExpression>
#include <QVector>
#include <QString>
#include <cmath>

EqualsCommand::EqualsCommand(calculator* calc)
    : _calc(calc),
    _prevInput(calc->currentInput()),
    _prevExpression(calc->expressionBuffer())
{}

void EqualsCommand::execute()
{
    QString expr = _prevExpression + _prevInput;
    if (expr.isEmpty()) return;
    {
        QRegularExpression resq(R"(√(-?\d+(?:\.\d+)?))");
        QRegularExpressionMatch m;
        while ((m = resq.match(expr)).hasMatch())
        {
            double v = m.captured(1).toDouble();
            expr.replace(m.capturedStart(), m.capturedLength(), QString::number(std::sqrt(v), 'g', 15));
        }
    }
    {
        QRegularExpression reln(R"(ln(-?\d+(?:\.\d+)?))");
        QRegularExpressionMatch m;
        while ((m = reln.match(expr)).hasMatch())
        {
            double v = m.captured(1).toDouble();
            expr.replace(m.capturedStart(), m.capturedLength(), QString::number(std::log(v), 'g', 15));
        }
    }
    QRegularExpression re(R"((\d+(?:\.\d+)?)|([+\-*/^()]))");
    auto it = re.globalMatch(expr);

    QVector<double> numbers;
    QVector<QString> ops;
    while (it.hasNext())
    {
        QString tok = it.next().captured(0);
        bool isNum = false;
        double val = tok.toDouble(&isNum);
        if (isNum)
            numbers.push_back(val);
        else
            ops.push_back(tok);
    }

    if (numbers.size() != ops.size() + 1)
    {
        qWarning() << "Parse error:" << "numbers=" << numbers.size() << "ops=" << ops.size();
        return;
    }

    const QVector<QVector<QString>> levels =
    {
        { "^"      },
        { "*", "/" },
        { "+", "-" }
    };
    for (auto &lvl : levels)
    {
        bool again;
        do
        {
            again = false;
            for (int i = 0; i < ops.size(); ++i)
            {
                const QString &op = ops[i];
                if (lvl.contains(op))
                {
                    double a = numbers[i];
                    double b = numbers[i+1];
                    double r = 0.0;
                    if      (op == "^") r = std::pow(a, b);
                    else if (op == "*") r = a * b;
                    else if (op == "/") r = b != 0.0 ? a/b : 0.0;
                    else if (op == "+") r = a + b;
                    else if (op == "-") r = a - b;

                    numbers[i] = r;
                    numbers.removeAt(i+1);
                    ops.removeAt(i);
                    again = true;
                    break;
                }
            }
        } while (again);
    }

    _result = numbers[0];
    QString out = QString::number(_result, 'f', 2);
    if (out.endsWith(".00")) out.chop(3);
    else if (out.endsWith("0") && out.contains('.')) out.chop(1);

    _calc->setExpressionBuffer(out);
    _calc->setCurrentInput("");
}

void EqualsCommand::undo()
{
    _calc->setCurrentInput(_prevInput);
    _calc->setExpressionBuffer(_prevExpression);
}
