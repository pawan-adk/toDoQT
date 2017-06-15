#include "task.h"
#include "ui_task.h"

#include <QInputDialog>
#include <QDebug>

Task::Task(const QString &task, QWidget *parent) :
    QWidget(parent),

    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(task);

    //slots
    connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
    connect(ui->checkBox, &QCheckBox::toggled, this,&Task::taskChecked);

    //signals
    connect(ui->removeButton, &QPushButton::clicked, [this] {
        emit removed(this);
    });
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name)
{
    ui->checkBox->setText(name);
}

QString Task::name() const
{
    return ui->checkBox->text();
}

bool Task::isCompleted() const
{
    return ui->checkBox->isChecked();
}

void Task::rename()
{
    bool ok;
    QString value = QInputDialog::getText(this, tr("Edit Task"), tr("Task Name"),QLineEdit::Normal, this->name(), &ok);

    if( ok && !value.isEmpty())
        setName(value);
}

void Task::taskChecked(bool checked)
{
    QFont font(ui->checkBox->font());
    font.setStrikeOut(checked);
    ui->checkBox->setFont(font);
    emit statusChanged(this);
}
