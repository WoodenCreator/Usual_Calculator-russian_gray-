#include "mainwindow.h"
#include "./ui_mainwindow.h"

double num;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton0, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton3, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton4, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton5, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton6, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton7, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton8, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton9, SIGNAL(clicked()), this, SLOT(numbers()));
    connect(ui->pushButton_sign, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_null, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_dem, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math()));
    connect(ui->pushButton_multi, SIGNAL(clicked()), this, SLOT(math()));

    ui->pushButton_div->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multi->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numbers()
{
    QPushButton *button = (QPushButton *)sender(); // отслеживает, на какую кнопку было произведено нажатие
    double all_numbers;
    QString res;
    if (button->text() == '0' && ui->label_main->text().contains("."))
    {
    res = (ui->label_main->text()+ button->text());
    }
    else
    {
    all_numbers = (ui->label_main->text()+ button->text()).toDouble();// позволяет сохранять в кнопке весь текст
    res = QString::number(all_numbers, 'g', 15);
    }
    ui->label_main->setText(res);
}

void MainWindow::on_pushButton_point_clicked()
{
    if (!(ui->label_main->text().contains('.'))) // !
        ui->label_main->setText(ui->label_main->text() + ".");//в условиях ставится обработчик текста
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString res;
     if (button->text() == "+/-")
     {
         all_numbers = (ui->label_main->text().toDouble());
         all_numbers = (-1)* all_numbers;
         res = QString::number(all_numbers, 'g', 15);

         ui->label_main->setText(res);
     }
     else if (button->text() == "AC")
     {
         all_numbers = 0.0;
         res = QString::number(all_numbers, 'g', 15);
         ui->label_main->setText(res);
         ui->label_extra->setText("");
         ui->pushButton_div->setChecked(false);
         ui->pushButton_plus->setChecked(false);
         ui->pushButton_minus->setChecked(false);
         ui->pushButton_multi->setChecked(false);
    }
     else if (button->text() == "%") // отследить количество нажатий
     {
         all_numbers = (ui->label_main->text().toDouble());
         all_numbers = 0.01 * all_numbers;
         res = QString::number(all_numbers, 'g', 15);
         ui->label_main->setText(res);
    }
}

void MainWindow:: math()
{
     QPushButton *button = (QPushButton *)sender();
     num = ui->label_main->text().toDouble();
     ui->label_main->setText("0");
     QString button_text = button->text();
     if(button_text == "+")
         ui->label_extra->setText(QString::number(num)+ QString::fromStdString(" + "));
     else if (button_text == "X")
         ui->label_extra->setText(QString::number(num)+ QString::fromStdString(" * "));
     else if(button_text == "/")
         ui->label_extra->setText(QString::number(num)+ QString::fromStdString(" / "));
     else if(button_text == "-")
        ui->label_extra->setText(QString::number(num)+ QString::fromStdString(" - "));

     button->setChecked(true);
}

void MainWindow::on_pushButton_equal_clicked()
{
    double fir = num;
    double first, second;
    QString new_;
    second = ui->label_main->text().toDouble();

    if(ui->pushButton_plus->isChecked())
    {
        first = num + second;
        new_ = QString::number(first, 'g', 15);
        ui->label_main->setText(new_);
        ui->label_extra->setText(QString::number(fir)  + " + " + QString::number(second)+ " = " +new_);
        ui->pushButton_plus->setChecked(false);
    }
    else if(ui->pushButton_multi->isChecked())
    {
        first = num * second;
        new_ = QString::number(first, 'g', 15);
        ui->label_main->setText(new_);
        ui->label_extra->setText(QString::number(fir)  + " * " + QString::number(second)+ " = " +new_);
        ui->pushButton_multi->setChecked(false);
    }
    else if(ui->pushButton_minus->isChecked())
    {
        first = num - second;
        new_ = QString::number(first, 'g', 15);
        ui->label_main->setText(new_);
        ui->label_extra->setText(QString::number(fir)  + " - " + QString::number(second)+ " = " +new_);
        ui->pushButton_minus->setChecked(false);
    }
    else if(ui->pushButton_div->isChecked())
    {
        first = num / second;
        if (second == 0)
           {
            ui->label_main->setText(QString::fromStdString("Error"));
            ui->label_extra->setText("Error");
            }
        else
        {
            new_ = QString::number(first, 'g', 15);
            ui->label_main->setText(new_);
             ui->label_extra->setText(QString::number(fir)  + " / " + QString::number(second)+ " = " +new_);
        }
        ui->pushButton_div->setChecked(false);
    }
}
