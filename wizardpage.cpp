#include "wizardpage.h"
#include "ui_wizardpage.h"

WizardPage::WizardPage(QWidget *parent, const QString &text) :
    QWizardPage(parent),
    ui(new Ui::WizardPage)
{
    ui->setupUi(this);

    ui->frame->setGraphicsEffect(newShadowEffect());

    QStringList list = text.split("==");
    QStringList reaList = list.at(0).split("|"), resList = list.at(1).split("|");
    vector<string> v, ream, resm;
    vector<int> reac, resc;
    for (int i = 0; i < reaList.count(); i++) {
        v.push_back(reaList.at(i).toStdString());
    }
    unpackage(v, ream, reac);
    v.clear();
    for (int i = 0; i < resList.count(); i++) {
        v.push_back(resList.at(i).toStdString());
    }
    unpackage(v, resm, resc);
    vector<int> num = balance(ream, reac, resm, resc);

    string qs, ts;
    for (int i = 0; i < (int)ream.size() - 1; i++) {
        qs += toHtml(ream[i], reac[i]) + '+';
        ts += itos(num[i]) + toHtml(ream[i], reac[i]) + '+';
    }
    qs += toHtml(ream[ream.size() - 1], reac[reac.size() - 1]) + "==";
    ts += itos(num[ream.size() - 1]) + toHtml(ream[ream.size() - 1], reac[reac.size() - 1]) + "==";
    int delta = ream.size();
    for (int i = 0; i < (int)resm.size() - 1; i++) {
        qs += toHtml(resm[i], resc[i]) + '+';
        ts += itos(num[i + delta]) + toHtml(resm[i], resc[i]) + '+';
    }
    qs += toHtml(resm[resm.size() - 1], resc[resc.size() - 1]);
    ts += itos(num[resm.size() - 1 + delta]) + toHtml(resm[resm.size() - 1], resc[resc.size() - 1]);
    questionText = QString::fromStdString(qs);
    QTextDocument d;
    d.setHtml(QString::fromStdString(ts));
    targetText = d.toPlainText();

#ifdef Q_OS_MAC
    ui->textEdit->setFont(QFont("Arial", 24));
#else
    ui->textEdit->setFont(QFont("Arial", 18));
#endif

    on_pushButton_clicked();
}

WizardPage::~WizardPage()
{
    delete ui;
}

QGraphicsDropShadowEffect* WizardPage::newShadowEffect() {
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 2);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(10);
    return shadow_effect;
}

bool WizardPage::correct() {
    return ui->textEdit->document()->toPlainText() == targetText;
}

void WizardPage::on_pushButton_clicked()
{
    ui->textEdit->setText(questionText);
}

void WizardPage::on_textEdit_textChanged()
{
    if (correct()) {
        ui->label->setText(tr("Correct"));
        ui->label->setStyleSheet("font-size: 18px; color: green");
    } else {
        ui->label->setText(tr("Error"));
        ui->label->setStyleSheet("font-size: 18px; color: red");
    }
}
