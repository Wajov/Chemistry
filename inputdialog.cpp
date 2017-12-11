#include "inputdialog.h"
#include "ui_inputdialog.h"
#include "character_set.h"
#include "core.h"
#include "elements_table.h"
#include <QPropertyAnimation>
#include <QDesktopWidget>
//#include <QDebug>

InputDialog::InputDialog(QWidget *parent, const QString &title, const QString &label) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    ui->label->setText(label);

    /* QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
    ui->dockWidget->hide();
    animation->setDuration(0);
    animation->setStartValue(this->size());
    animation->setEndValue(QSize(400, 100));
    animation->start(); */
    this->resize(QSize(400, 0));
    ui->dockWidget->resize(QSize(650, 300));
    ui->dockWidget->move((QApplication::desktop()->width() - ui->dockWidget->width())/2,
                         QApplication::desktop()->height() - ui->dockWidget->height() - 100);
    ui->dockWidget->hide();

    for (int i = '0'; i <= '9'; i++) {
        ui->numbersListWidget->addItem(QString(i));
    }
    QStringList list;
    list << "+" << "-" << "(" << ")";
    ui->numbersListWidget->addItems(list);

    setTableWidget(ui->elementsTableWidget, QFont("Times New Roman", 12));
}

InputDialog::~InputDialog()
{
    delete ui;
}

QString InputDialog::text()
{
    return ui->lineEdit->text();
}

void InputDialog::on_elementsTableWidget_clicked()
{
    QString text = ui->lineEdit->text(), itemText = ui->elementsTableWidget->currentItem()->text();
    text += itemText != "La-Lu" && itemText != "Ac-Lr" ? itemText : "";
    ui->lineEdit->setText(text);
}

void InputDialog::on_numbersListWidget_clicked()
{
    QString text = ui->lineEdit->text();
    text += ui->numbersListWidget->currentItem()->text();
    ui->lineEdit->setText(text);
}

/* void InputDialog::on_toolBox_currentChanged(int index)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
    if (index == 0) {
        animation->setDuration(200);
        animation->setStartValue(this->size());
        animation->setEndValue(QSize(850, 500));
        animation->start();
    } else {
        animation->setDuration(200);
        animation->setStartValue(this->size());
        animation->setEndValue(QSize(850, 350));
        animation->start();
    }
} */

void InputDialog::on_spacePushButton_clicked()
{
    QString text = ui->lineEdit->text();
    text += " ";
    ui->lineEdit->setText(text);
}

void InputDialog::on_backspacePushButton_clicked()
{
    QString text = ui->lineEdit->text();
    text = text.mid(0, text.size() - 1);
    ui->lineEdit->setText(text);
}

void InputDialog::on_quickInputPushButton_clicked()
{
    ui->dockWidget->show();
    /* QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
    if (ui->dockWidget->isHidden()) {
        ui->dockWidget->show();
        ui->quickInputPushButton->setText("隐藏快捷输入");
        animation->setDuration(200);
        animation->setStartValue(this->size());
        animation->setEndValue(QSize(670, 500));
        animation->start();
    } else {
        ui->dockWidget->hide();
        ui->quickInputPushButton->setText("显示快捷输入");
        animation->setDuration(200);
        animation->setStartValue(this->size());
        animation->setEndValue(QSize(400, 100));
        animation->start();
    } */
}
