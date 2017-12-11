#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFile config(QString("%1/config").arg(qApp->applicationDirPath()));
    bool b;
    b = config.open(QFile::ReadOnly);
    if (b) {
        QTextStream in(&config);
        in >> inputMode >> language >> qAppStyle;
        config.close();
    } else {
        inputMode = language = 0;
    }

    QTranslator *appTranslator = new QTranslator(this);
    QTranslator *qtTranslator = new QTranslator(this);
    if (language == 0) {
        appTranslator->load(":/chemistry_zh_CN.qm");
        qtTranslator->load(":/qt_zh_CN.qm");
    } else {
        appTranslator->load("");
        qtTranslator->load("");
    }
    qApp->installTranslator(appTranslator);
    qApp->installTranslator(qtTranslator);

    ui->setupUi(this);

    ui->reactantFrame->setGraphicsEffect(newShadowEffect());
    ui->productFrame->setGraphicsEffect(newShadowEffect());
    ui->elementsTableWidget->setGraphicsEffect(newShadowEffect());
    ui->headlineFrame->setGraphicsEffect(newShadowEffect());
    ui->resultFrame->setGraphicsEffect(newShadowEffect());

#ifdef Q_OS_WIN
    qApp->setStyleSheet("QLabel, QPushButton {font-family: \"Segoe UI\", \"Arial\", \"Microsoft YaHei\";}");
#endif

#ifdef Q_OS_MAC
    setTableWidget(ui->elementsTableWidget, QFont("Arial", 16));
    ui->textBrowser->setFont(QFont("Arial", 24));
#else
    setTableWidget(ui->elementsTableWidget, QFont("Arial", 12));
    ui->textBrowser->setFont(QFont("Arial", 18));
#endif

    QStringList keyList = QStyleFactory::keys();
    QActionGroup *styleGroup = new QActionGroup(this);
    for (int i = 0; i < keyList.size(); i++) {
        QAction *action = styleGroup->addAction(keyList.at(i));
        action->setCheckable(true);
        if (action->text() == qAppStyle) {
            set_qapp_style(action);
        }
    }
    ui->styleMenu->addActions(styleGroup->actions());

    QActionGroup *inputModeGroup = new QActionGroup(this);
    QAction *garphicModeAction = inputModeGroup->addAction(tr("Garphic Input"));
    garphicModeAction->setCheckable(true);
    QAction *textModeAction = inputModeGroup->addAction(tr("Text Input"));
    textModeAction->setCheckable(true);
    set_input_mode(inputMode == 0 ? garphicModeAction : textModeAction);
    inputModeMenu = new QMenu(this);
    inputModeMenu->addActions(inputModeGroup->actions());
    //ui->penPushButton->setMenu(inputModeMenu);

    QActionGroup *pageGroup = new QActionGroup(this);
    page1Action = pageGroup->addAction(tr("Equation Balancer"));
    page1Action->setCheckable(true);
    page2Action = pageGroup->addAction(tr("The Periodic Table of Chemical Elements"));
    page2Action->setCheckable(true);
    set_page(page1Action);
    QMenu *buttonMenu = new QMenu(this);
    buttonMenu->addActions(pageGroup->actions());
    buttonMenu->addSeparator();
    buttonMenu->addAction(ui->wizardAction);
    ui->pushButton->setMenu(buttonMenu);

    QActionGroup *languageGroup = new QActionGroup(this);
    QAction *scAction = languageGroup->addAction(tr("Simplified Chinese"));
    scAction->setCheckable(true);
    QAction *enAction = languageGroup->addAction(tr("English"));
    enAction->setCheckable(true);
    ui->languageMenu->addActions(languageGroup->actions());
    language == 0 ? scAction->setChecked(true) : enAction->setChecked(true);

    connect(styleGroup, SIGNAL(triggered(QAction*)), this, SLOT(set_qapp_style(QAction*)));
    connect(inputModeGroup, SIGNAL(triggered(QAction*)), this, SLOT(set_input_mode(QAction*)));
    connect(pageGroup, SIGNAL(triggered(QAction*)), this, SLOT(set_page(QAction*)));
    connect(languageGroup, SIGNAL(triggered(QAction*)), this, SLOT(set_qapp_language(QAction*)));
    connect(ui->aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
    QFile config(QString("%1/config").arg(qApp->applicationDirPath()));
    config.open(QFile::WriteOnly);
    QTextStream out(&config);
    out << inputMode << " " << language << " " << qAppStyle << endl;
    config.close();

    delete ui;
}

void MainWindow::displayAnimation() {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(200);
    animation->setStartValue(this->pos());
    animation->setKeyValueAt(0.2, QPoint(this->x() + 20, this->y()));
    animation->setKeyValueAt(0.4, QPoint(this->x() - 20, this->y()));
    animation->setKeyValueAt(0.6, QPoint(this->x() + 20, this->y()));
    animation->setKeyValueAt(0.8, QPoint(this->x() - 20, this->y()));
    animation->setEndValue(this->pos());
    animation->start();
}

void MainWindow::resizeWindow(int w, int h) {
    if (!(this->isFullScreen() || this->isMaximized())) {
        QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
        animation->setDuration(200);
        animation->setStartValue(this->size());
        animation->setEndValue(QSize(w, h));
        animation->start();
    }
}

QString MainWindow::inputDialog(const int &mode, const QString &title) {
    QString text;
    if (mode == 0) {
        InputBox d(this, tr("Add %1").arg(title), tr("Click to add a %1").arg(title));
        bool ok = d.exec();
        text = ok ? d.text() : "";
    } else {
        bool ok;
        text = QInputDialog::getText(this, tr("Add %1").arg(title),
                                     tr("Please input one or some %1(s), diffient %1 separated by a space.").arg(title),
                                     QLineEdit::Normal, "", &ok);
        text = ok ? text : "";
    }
    return text;
}

QGraphicsDropShadowEffect* MainWindow::newShadowEffect() {
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 2);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(10);
    return shadow_effect;
}

void MainWindow::set_qapp_style(QAction *action) {
    action->setChecked(true);
    qAppStyle = action->text();
    qApp->setStyle(QStyleFactory::create(qAppStyle));
}

void MainWindow::set_page(QAction *action) {
    action->setChecked(true);
    QString text = action->text();
    if (action == page1Action) {
        ui->pushButton->setText(text);
        ui->buttonFrame->setMaximumWidth(660);
        ui->stackedWidget->setMaximumWidth(660);
        ui->stackedWidget->setCurrentIndex(0);
        ui->penPushButton->setHidden(false);
        resizeWindow(480, this->height());
    } else {
        ui->pushButton->setText(text);
        ui->buttonFrame->setMaximumWidth(800);
        ui->stackedWidget->setMaximumWidth(800);
        ui->stackedWidget->setCurrentIndex(1);
        ui->penPushButton->setHidden(true);
        resizeWindow(800, this->height());
    }
}

void MainWindow::set_input_mode(QAction *action) {
    action->setChecked(true);
    QString text = action->text();
    //ui->penPushButton->setText(text);
    if (text == tr("Garphic Input")) {
        inputMode = 0;
    } else {
        inputMode = 1;
    }
}

void MainWindow::set_qapp_language(QAction *action) {
    QString text = action->text();
    if (text == tr("Simplified Chinese")) {
        language = 0;
    } else {
        language = 1;
    }
    QMessageBox::information(this, tr("Information"), tr("The language change will take effect after a restart of App."));
}

void MainWindow::on_reactantAddButton_clicked()
{
    QString text = inputDialog(inputMode, tr("reactant"));
    if (!text.isEmpty()) {
        QStringList list = text.split(" ", QString::SkipEmptyParts);
        for (int i = 0; i < list.size(); i++) {
            ui->reactantListWidget->addItem(list[i]);
        }
    }
}

void MainWindow::on_reactantDelButton_clicked()
{
    ui->reactantListWidget->takeItem(ui->reactantListWidget->currentRow());
}

void MainWindow::on_productAddButton_clicked()
{
    QString text = inputDialog(inputMode, tr("product"));
    if (!text.isEmpty()) {
        QStringList list = text.split(" ", QString::SkipEmptyParts);
        for (int i = 0; i < list.size(); i++) {
            ui->productListWidget->addItem(list[i]);
        }
    }
}

void MainWindow::on_productDelButton_clicked()
{
    ui->productListWidget->takeItem(ui->productListWidget->currentRow());
}

void MainWindow::on_aboutAction_triggered()
{
    QMessageBox::about(this, tr("About %1").arg(this->windowTitle()),
                       "<span style = \"font-size: 14px;\"><b>"
                       + tr("This App can help you to balance chemistry equations and solve other problems.") + "</b></span><br><br>"
                       + tr("UI designed by <b>Chen Sheng</b>, Qt version witten by <b>Chen Sheng, Wang Anjie</b>.") + "<br>"
                       + tr("The first version of Free Pascal wirtten by <b>Wang Anjie</b>."));
}

void MainWindow::on_helpAction_triggered()
{
    QMessageBox::information(this, tr("How to Use"), tr("View readme.pdf in directory."));
}

void MainWindow::on_elementsTableWidget_cellClicked(int row, int column)
{
    if (ui->elementsTableWidget->item(row, column)->flags() == Qt::NoItemFlags) {
        return;
    }
    QString currentElement = ui->elementsTableWidget->item(row, column)->text(), text;
    int i;
    for (i = 1; currentElement != QString::fromStdString(element[i]) && i < 113; i++);
    currentElement = "<span style = \"font-size: 24px;\">" + currentElement + " </span>" + QString(tr("The %1th element")).arg(i);
    text = QString(tr(", the %1th period %2 group."))\
            .arg(ui->elementsTableWidget->verticalHeaderItem(row)->text())\
            .arg(ui->elementsTableWidget->horizontalHeaderItem(column)->text());
    ui->label->setText(row < 7 ? currentElement + text : currentElement + tr("."));
}

void MainWindow::on_actionSample0_triggered()
{
    on_clearCommandLinkButton_clicked();
    ui->reactantListWidget->addItems(QStringList() << "H2O");
    ui->productListWidget->addItems(QStringList() << "H2" << "O2");
}

void MainWindow::on_actionSample1_triggered()
{
    on_clearCommandLinkButton_clicked();
    ui->reactantListWidget->addItems(QStringList() << "MnO2" << "HCl");
    ui->productListWidget->addItems(QStringList() << "Cl2" << "MnCl2" << "H2O");
}

void MainWindow::on_actionSample3_triggered()
{
    on_clearCommandLinkButton_clicked();
    ui->reactantListWidget->addItems(QStringList() << "Ba2+" << "(SO4)2-");
    ui->productListWidget->addItems(QStringList() << "BaSO4");
}

void MainWindow::on_commandLinkButton_clicked()
{
    if (ui->reactantListWidget->count() == 0 || ui->productListWidget->count() == 0) {
        displayAnimation();
        ui->statusBar->showMessage(tr("No reactant or prodect."));
        return;
    }

    vector<string> v, ream, resm;
    vector<int> reac, resc;
    for (int i = 0; i < ui->reactantListWidget->count(); i++) {
        v.push_back(ui->reactantListWidget->item(i)->text().toStdString());
    }
    unpackage(v, ream, reac);
    v.clear();
    for (int i = 0; i < ui->productListWidget->count(); i++) {
        v.push_back(ui->productListWidget->item(i)->text().toStdString());
    }
    unpackage(v, resm, resc);

    vector<int> num = balance(ream, reac, resm, resc);
    if (num.empty()) {
        displayAnimation();
        ui->statusBar->showMessage(tr("Cannot balancing! Check if there was anything wrong in input."));
        return;
    }

    string text;
    for (int i = 0; i < (int)ream.size() - 1; i++) {
        text += itos(num[i]) + toHtml(ream[i], reac[i]) + '+';
    }
    text += itos(num[ream.size() - 1]) + toHtml(ream[ream.size() - 1], reac[reac.size() - 1]) + "==";
    int delta = ream.size();
    for (int i = 0; i < (int)resm.size() - 1; i++) {
        text += itos(num[i + delta]) + toHtml(resm[i], resc[i]) + '+';
    }
    text += itos(num[resm.size() - 1 + delta]) + toHtml(resm[resm.size() - 1], resc[resc.size() - 1]);
    //text = "<span style = \"font: normal 24px;\">" + text + "</span>";
    ui->textBrowser->setHtml(QString::fromStdString(text));
    //ui->headlineLabel->setText(tr("Result"));
    ui->stackedWidget->setCurrentIndex(2);
    //QMessageBox::information(this, tr("Result"), QString::fromStdString(text));
}

void MainWindow::on_clearCommandLinkButton_clicked()
{
    ui->reactantListWidget->clear();
    ui->productListWidget->clear();
    ui->statusBar->showMessage(tr("Cleared."));
}

void MainWindow::on_wizardAction_triggered()
{
    QFile file(QString("%1/checkpoint").arg(qApp->applicationDirPath()));
    bool b;
    b = file.open(QFile::ReadOnly);
    if (!b) {
        displayAnimation();
        ui->statusBar->showMessage(tr("Checkpoint file not exist."));
        //QMessageBox::warning(this, tr("Warning"), tr("Checkpoint file not exist."));
        return;
    }
    QTextStream in(&file);
    int k, n;
    QString s;
    QStringList sl, items;
    QList<QStringList> textList;
    in >> k;
    for (int i = 0; i < k; i++) {
        sl.clear();
        in >> s;
        items.push_back(s);
        in >> n;
        for (int j = 0; j < n; j++) {
            in >> s;
            sl.push_back(s);
        }
        textList.push_back(sl);
    }
    file.close();

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Choose a Checkpoint"),
                                         tr("Choose a checkpoint to challenge."), items, 0, false, &ok);
    if (ok && !item.isEmpty()) {
        QWizard w;
        w.setWizardStyle(QWizard::ModernStyle);
        int index = 0;
        for (; index < items.count() && items.at(index) != item; index++);
        QList<WizardPage *> pages;
        QStringList list = textList.at(index);
        for (int i = 0; i < list.count(); i++) {
            pages.push_back(new WizardPage(this, list.at(i)));
            w.addPage(pages.back());
        }
        if (w.exec()) {
            int count = 0;
            for (int i = 0; i < pages.count(); i++) {
                count += pages.at(i)->correct();
            }
            QMessageBox::information(this, tr("Result"), tr("Completed %1 of %2 question(s).").arg(count).arg(pages.count()));
        }
    }
}

void MainWindow::on_backPushButton_clicked()
{
    set_page(page1Action);
}

void MainWindow::on_penPushButton_clicked()
{
    int x = ui->penPushButton->sizeHint().width() - inputModeMenu->sizeHint().width();
    inputModeMenu->exec(ui->penPushButton->mapToGlobal(QPoint(x, ui->penPushButton->sizeHint().height())));
}
