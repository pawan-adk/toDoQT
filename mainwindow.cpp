#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(ui->addTaskButton, &QPushButton::clicked,
            QApplication::instance(), &QApplication::quit);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
