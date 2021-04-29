#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "lib/password.h"
#include "lib/exceptions.h"

#include <QMessageBox>
#include <QClipboard>

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

void MainWindow::generate()
{
    int length =  ui->spinBox_length->value();
    bool lowercase = ui->checkBox_lowercase->checkState();
    bool uppercase = ui->checkBox_uppercase->checkState();
    bool numbers = ui->checkBox_numbers->checkState();
    bool specials = ui->checkBox_specials->checkState();

    std::string result = "";

    try {
        result = generatePassword(length, lowercase, uppercase, numbers, specials);
        ui->label_password->setText(QString::fromStdString(result));
    }  catch (const ZeroLengthPassword& e) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "You can't have a zero-length password!");
    } catch (const NoTypesError& e) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "You can't have a password without symbols!");
    }
}

void MainWindow::copy()
{
    std::string password = ui->label_password->text().toStdString();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(QString::fromStdString(password));
}
