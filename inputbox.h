#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QDialog>
#include <QGraphicsDropShadowEffect>
#include "elements_table.h"
#include "core.h"

namespace Ui {
class InputBox;
}

class InputBox : public QDialog
{
    Q_OBJECT

public:
    explicit InputBox(QWidget *parent = 0, const QString &title = "", const QString &label = "");
    ~InputBox();
    QString text();

private slots:
    void on_checkBox_clicked(bool checked);

    void on_tableWidget_cellClicked(int row, int column);

    void on_delPushButton_clicked();

    void on_dial_valueChanged(int value);

    void on_tableWidget_2_cellClicked(int row, int column);

private:
    Ui::InputBox *ui;
    QStringList list;
    int charge;
    void showItems();
    QGraphicsDropShadowEffect* newShadowEffect();
};

#endif // INPUTBOX_H
