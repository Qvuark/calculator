#include "calculator.h"
#include "ui_calculator.h"
#include <QPushButton>
#include <QDebug>

calculator::calculator(QWidget *parent) : QWidget(parent), ui(new Ui::calculator), currentInput("0")
{
    ui->setupUi(this);
    auto connectDigit = [this](QPushButton* btn) {
        connect(btn, &QPushButton::released, [this, btn]() {
            handleDigitPress(btn->text());
        });
    };

    connectDigit(ui->pushBtn_0);
    connectDigit(ui->pushBtn_1);
    connectDigit(ui->pushBtn_2);
    connectDigit(ui->pushBtn_3);
    connectDigit(ui->pushBtn_4);
    connectDigit(ui->pushBtn_5);
    connectDigit(ui->pushBtn_6);
    connectDigit(ui->pushBtn_7);
    connectDigit(ui->pushBtn_8);
    connectDigit(ui->pushBtn_9);

    setStyleSheet("background-color: white;");
    updateDisplay();
}

calculator::~calculator()
{
    delete ui;
}

void calculator::updateDisplay()
{
    ui->screen->setText(currentInput);
}

void calculator::handleDigitPress(const QString &digit)
{
    if(currentInput.length() >= 15) return;
    if(currentInput.contains("."))
    {
        QStringList parts = currentInput.split(".");
        if(parts.size() > 1 && parts[1].length() >= 10) return;
    }
    else
    {
        if(currentInput == "0" && digit != "0") { currentInput.clear(); }
        else if(currentInput == "0" && digit == "0") {return;}
    }

    currentInput += digit;
    updateDisplay();
}

void calculator::on_pushBtn_FloatingPoint_released()
{
    if(currentInput.contains('.') || currentInput.length() >= 15) return;

    if(currentInput.isEmpty() || currentInput.endsWith("+") ||
        currentInput.endsWith("-") || currentInput.endsWith("×") ||
        currentInput.endsWith("÷")) {
        currentInput += "0.";
    }
    else {currentInput += ".";}

    updateDisplay();
}

void calculator::on_pushBtn_00_released()
{
    if(currentInput.length() >= 14) return;

    if(currentInput == "0") {return;}
    else { currentInput += "00";}

    updateDisplay();
}
