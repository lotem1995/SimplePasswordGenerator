#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_passwordLength_actionTriggered(int action)
{
    length=action;
    ui->displayLength->display(length);
}


void MainWindow::on_charSpecial_stateChanged(int arg1)
{
    if (arg1!=0)
        special=1;
    else special=0;
}


void MainWindow::on_charUpperCase_stateChanged(int arg1)
{
    if (arg1!=0)
        upper_case_letters=1;
    else upper_case_letters=0;
}


void MainWindow::on_charNumbers_stateChanged(int arg1)
{
    if (arg1!=0)
        numbers=1;
    else numbers=0;
}


void MainWindow::on_charLowerCase_stateChanged(int arg1)
{
    if (arg1!=0)
        lower_case_letters=1;
    else lower_case_letters=0;
}


void MainWindow::on_commandLinkButton_clicked()
{
    generated.Init(length);
    generated.generate(numbers,lower_case_letters,upper_case_letters,special);
    ui->Output->setPlainText(generated.password);
}

void MainWindow::on_passwordLength_valueChanged(int value)
{
    length=value;
    ui->displayLength->display(length);
}


void MainWindow::on_actionAbout_triggered()
{
    ui->Output->setPlainText(QString("A simple password generator, made by Lotem Sakira"));
}


void MainWindow::on_actionReset_triggered()
{
    length=8;
    upper_case_letters=0;
    lower_case_letters=0;
    numbers=0;
    special=0;
    ui->displayLength->display(length);
    ui->passwordLength->setValue(length);
    ui->charNumbers->setChecked(numbers);
    ui->charLowerCase->setChecked(lower_case_letters);
    ui->charUpperCase->setChecked(upper_case_letters);
    ui->charSpecial->setChecked(special);
}


void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::exit();
}

void MainWindow::on_lengthSpin2_valueChanged(int arg1)
{
    length=arg1;
    ui->lengthSlider2->setValue(length);
    //ui->outputSpecific->setPlainText(QStringLiteral("%1").arg(length));
}


void MainWindow::on_lengthSlider2_valueChanged(int value)
{
    length=value;
    ui->lengthSpin2->setValue(length);
    //ui->outputSpecific->setPlainText(QStringLiteral("%1").arg(length));
}


void MainWindow::on_charNumbers2_valueChanged(int arg1)
{
    numbers=arg1;
}


void MainWindow::on_charUpper2_valueChanged(int arg1)
{
    upper_case_letters=arg1;
}


void MainWindow::on_charLower2_valueChanged(int arg1)
{
    lower_case_letters=arg1;
}



void MainWindow::on_charSpecial2_valueChanged(int arg1)
{
    special=arg1;
}


void MainWindow::on_executeSpecific_clicked()
{
    int validation=numbers+upper_case_letters+lower_case_letters+special;
    if (validation==0||length==0)
        ui->outputSpecific->setPlainText("nice try");
    else if(validation>length)
        ui->outputSpecific->setPlainText(QStringLiteral("please reduce the number of characters requested by %1").arg(validation-length));
    else if(length>validation)
        ui->outputSpecific->setPlainText(QStringLiteral("please increase the number of characters requested by %1").arg(length-validation));
    else{
        generated.Init(length);
        generated.generateSpecific(numbers,lower_case_letters,upper_case_letters,special);
        ui->outputSpecific->setPlainText(generated.password);
    }
}

