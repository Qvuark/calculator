#include "calculator.h"

calculator::calculator(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);
    setStyleSheet("background-color: white;");
    // Connect button signal to slot
    /*connect(ui->btn1, &QPushButton::clicked,
            this, &calculator::handleButtonClick);*/
}

calculator::~calculator()
{
    delete ui;
}

void calculator::handleButtonClick()
{
    // Your calculator logic here
    ui->label->setText("Button clicked!");
}
