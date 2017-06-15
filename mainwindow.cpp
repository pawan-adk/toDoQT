#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{   bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Add task"),
                                         tr("Add name"),
                                         QLineEdit::Normal,
                                         tr("Untitled Task"),&ok);
    if(ok && !name.isEmpty()){
        qDebug()<<"The button is pressed";
        Task* task = new Task(name);
        connect(task, &Task::removed, this, &MainWindow::removeTask); //when we are creating the new task then it should be connected to slot
        mTasks.append(task);
        ui->tasksLayout->addWidget(task);
    }

}

void MainWindow::removeTask(Task *task) //This signature must match the one coming from the signal
{
    qDebug()<<"The signal is recieved to remove";
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(nullptr);
    delete task;
}
