#include "inputbox.h"
#include "ui_inputbox.h"

InputBox::InputBox(QWidget *parent, const QString &title, const QString &label) :
    QDialog(parent),
    ui(new Ui::InputBox)
{
    ui->setupUi(this);

    this->setWindowTitle(title);
    ui->label->setText(label);

    ui->frame->setGraphicsEffect(newShadowEffect());
    ui->frame_2->setGraphicsEffect(newShadowEffect());
    ui->frame_3->setGraphicsEffect(newShadowEffect());

    charge = 0;

#ifdef Q_OS_MAC
    setTableWidget(ui->tableWidget, QFont("Arial", 12));
#else
    setTableWidget(ui->tableWidget, QFont("Arial", 9));
#endif

    for (int i = 0; i <= 9; i++) {
        ui->tableWidget_2->setItem(0, i, new QTableWidgetItem(QString(i + '0')));
    }
    ui->tableWidget_2->setItem(0, 10, new QTableWidgetItem("("));
    ui->tableWidget_2->setItem(0, 11, new QTableWidgetItem(")"));
    //ui->tableWidget_2->setItem(0, 12, new QTableWidgetItem("["));
    //ui->tableWidget_2->setItem(0, 13, new QTableWidgetItem("]"));
    for (int i = 0; i <= 11; i++) {
        ui->tableWidget_2->item(0, i)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_2->item(0, i)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    }
}

InputBox::~InputBox()
{
    delete ui;
}

void InputBox::showItems()
{
    QString text;
    for (int i = 0; i < list.size(); i++) {
        if (isdigit(list[i][0].toLatin1())) {
            text += "<sub>" + list[i] + "</sub>";
        } else {
            text += list[i];
        }
    }
    if (ui->checkBox->isChecked() && charge != 0) {
        text += "<sup>" + QString::fromStdString(itos(charge)) + (charge > 0 ? "+" : "-") + "</sup>";
    }
    ui->label->setText(text);
}

QGraphicsDropShadowEffect* InputBox::newShadowEffect() {
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 2);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(10);
    return shadow_effect;
}

QString InputBox::text() {
    QString text = list.join("");
    if (ui->checkBox->isChecked()) {
        text = "(" + text + ")" + QString::fromStdString(itos(charge)) + (charge > 0 ? "+" : "-");
    }
    return text;
}

void InputBox::on_checkBox_clicked(bool checked)
{
    ui->dial->setEnabled(checked);
    ui->lcdNumber->setEnabled(checked);
    showItems();
}

void InputBox::on_tableWidget_cellClicked(int row, int column)
{
    if (ui->tableWidget->item(row, column)->flags() == Qt::NoItemFlags) {
        return;
    }
    QString item = ui->tableWidget->item(row, column)->text();
    list.push_back(item);
    showItems();
}

void InputBox::on_delPushButton_clicked()
{
    if(!list.empty()) {
        list.pop_back();
    }
    showItems();
}

void InputBox::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
    charge = value;
    showItems();
}

void InputBox::on_tableWidget_2_cellClicked(int row, int column)
{
    QString item = ui->tableWidget_2->item(row, column)->text();
    list.push_back(item);
    showItems();
}
