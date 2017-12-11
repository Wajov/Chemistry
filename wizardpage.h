#ifndef WIZARDPAGE_H
#define WIZARDPAGE_H

#include <QWizardPage>
#include "core.h"
#include <QGraphicsDropShadowEffect>
#include "QDebug"

namespace Ui {
class WizardPage;
}

class WizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WizardPage(QWidget *parent = 0, const QString &text = "");
    ~WizardPage();
    bool correct();

private slots:
    void on_pushButton_clicked();

    void on_textEdit_textChanged();

private:
    Ui::WizardPage *ui;
    QString questionText;
    QString targetText;
    QGraphicsDropShadowEffect* newShadowEffect();
};

#endif // WIZARDPAGE_H
