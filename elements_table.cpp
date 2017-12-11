#include "elements_table.h"

void setTableWidget(QTableWidget *tableWidget, QFont font) {
    tableWidget->setRowCount(10);
    tableWidget->setColumnCount(18);
    tableWidget->setHorizontalHeaderLabels(
                QStringList(QStringList() << "IA" << "IIA" << "IIIB" << "IVB" << "VB" << "VIB" << "VIIB" << "VIII"
                            << "VIII" << "VIII" << "IB" << "IIB" << "IIIA" << "IVA" << "VA" << "VIA" << "VIIA" << "0"));
    tableWidget->setVerticalHeaderLabels(
                QStringList(QStringList() << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "" << "La-Lu" << "Ac-Lr"));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 18; j++) {
            tableWidget->setItem(i, j, new QTableWidgetItem(""));
            tableWidget->item(i, j)->setFont(font);
            tableWidget->item(i, j)->setFlags(Qt::NoItemFlags);
            tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    int count = 1;
    tableWidget->item(0, 0)->setText(QString::fromStdString(element[count++]));
    tableWidget->item(0, 17)->setText(QString::fromStdString(element[count++]));
    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            tableWidget->item(i, j)->setText(QString::fromStdString(element[count++]));
        }
        for (int j = 12; j < 18; j++) {
            tableWidget->item(i, j)->setText(QString::fromStdString(element[count++]));
        }
    }
    for (int i = 3; i < 5; i++) {
        for (int j = 0; j < 18; j++) {
            tableWidget->item(i, j)->setText(QString::fromStdString(element[count++]));
        }
    }
    for (int i = 5; i < 7; i++) {
        for (int j = 0; j < 18; j++) {
            if (j == 2) {
                if (i == 5) {
                    tableWidget->item(i, j)->setText("La-Lu");
                } else {
                    tableWidget->item(i, j)->setText("Ac-Lr");
                }
                count += 15;
            } else if (count < 113) {
                tableWidget->item(i, j)->setText(QString::fromStdString(element[count++]));
            }
        }
    }
    for (int j = 0; j < 15; j++) {
        tableWidget->item(8, j)->setText(QString::fromStdString(element[57 + j]));
    }
    for (int j = 0; j < 15; j++) {
        tableWidget->item(9, j)->setText(QString::fromStdString(element[89 + j]));
    }

    const QColor green(198, 255, 159), blue(117, 218, 252), yellow(255, 255, 157);
    tableWidget->item(0, 0)->setBackgroundColor(blue);
    tableWidget->item(0, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    tableWidget->item(0, 17)->setBackgroundColor(blue);
    tableWidget->item(0, 17)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    for (int i = 0; i < 5; i++) {
        for (int j = i; j < 6; j++) {
            tableWidget->item(i + 1, j + 12)->setBackgroundColor(blue);
            tableWidget->item(i + 1, j + 12)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
    for (int i = 3; i < 7; i++) {
        for (int j = 2; j < 12; j++) {
            tableWidget->item(i, j)->setBackgroundColor(green);
            tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < 2; j++) {
            tableWidget->item(i, j)->setBackgroundColor(yellow);
            tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= i; j++) {
            tableWidget->item(i + 2, j + 12)->setBackgroundColor(yellow);
            tableWidget->item(i + 2, j + 12)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
    for (int i = 8; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            tableWidget->item(i, j)->setBackgroundColor(green);
            tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }
    tableWidget->item(5, 2)->setFlags(Qt::NoItemFlags);
    tableWidget->item(6, 2)->setFlags(Qt::NoItemFlags);
}
