#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>


calculator::calculator(QWidget *parent) : QWidget(parent), ui(new Ui::calculator)
{
    ui->setupUi(this);
    connect(ui->pushBtn_0, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_1, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_2, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_3, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_4, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_5, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_6, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_7, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_8, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->pushBtn_9, SIGNAL(released()), this, SLOT(digitPressed()));
    setStyleSheet("background-color: white;");
}

calculator::~calculator()
{
    delete ui;
}

void calculator::digitPressed()
{
    qDebug()<< "test";
}
