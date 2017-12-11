#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = 0, const QString &title = "", const QString &label = "");
    ~InputDialog();
    QString text();

private slots:
    void on_elementsTableWidget_clicked();

    void on_numbersListWidget_clicked();

    //void on_toolBox_currentChanged(int index);

    void on_spacePushButton_clicked();

    void on_backspacePushButton_clicked();

    void on_quickInputPushButton_clicked();

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
