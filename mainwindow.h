#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core.h"
#include "elements_table.h"
#include "inputbox.h"
#include "wizardpage.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QDebug>
#include <QFile>
#include <QStyleFactory>
#include <QGraphicsDropShadowEffect>
#include <QWizard>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void set_qapp_style(QAction *action);

    void set_page(QAction *action);

    void set_input_mode(QAction *action);

    void set_qapp_language(QAction *action);

    void on_reactantAddButton_clicked();

    void on_reactantDelButton_clicked();

    void on_productAddButton_clicked();

    void on_productDelButton_clicked();

    void on_aboutAction_triggered();

    void on_helpAction_triggered();

    void on_elementsTableWidget_cellClicked(int row, int column);

    void on_actionSample0_triggered();

    void on_actionSample1_triggered();

    void on_actionSample3_triggered();

    void on_commandLinkButton_clicked();

    void on_clearCommandLinkButton_clicked();

    void on_wizardAction_triggered();

    void on_backPushButton_clicked();

    void on_penPushButton_clicked();

private:
    Ui::MainWindow *ui;
    int inputMode;
    int language;
    QString qAppStyle;
    QAction *page1Action;
    QAction *page2Action;
    QMenu *inputModeMenu;
    void displayAnimation();
    void resizeWindow(int w, int h);
    QString inputDialog(const int &mode, const QString &title);
    QGraphicsDropShadowEffect* newShadowEffect();
};

#endif // MAINWINDOW_H
