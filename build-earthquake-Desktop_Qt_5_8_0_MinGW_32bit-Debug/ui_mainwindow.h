/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QCustomPlot *plot1;
    QCustomPlot *plot2;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *map;
    QWidget *top;
    QLabel *label1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *highDate;
    QLabel *highMag;
    QLabel *highLat;
    QLabel *highLong;
    QLabel *highDepth;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 600);
        MainWindow->setMinimumSize(QSize(800, 500));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(800, 500));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        plot1 = new QCustomPlot(centralWidget);
        plot1->setObjectName(QStringLiteral("plot1"));

        verticalLayout->addWidget(plot1);

        plot2 = new QCustomPlot(centralWidget);
        plot2->setObjectName(QStringLiteral("plot2"));

        verticalLayout->addWidget(plot2);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, -1, -1, 0);
        map = new QCustomPlot(centralWidget);
        map->setObjectName(QStringLiteral("map"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(map->sizePolicy().hasHeightForWidth());
        map->setSizePolicy(sizePolicy);
        map->setMinimumSize(QSize(400, 288));
        map->setMaximumSize(QSize(400, 288));

        verticalLayout_3->addWidget(map);

        top = new QWidget(centralWidget);
        top->setObjectName(QStringLiteral("top"));
        top->setMinimumSize(QSize(400, 264));

        verticalLayout_3->addWidget(top);

        label1 = new QLabel(centralWidget);
        label1->setObjectName(QStringLiteral("label1"));

        verticalLayout_3->addWidget(label1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 0, -1);
        highDate = new QLabel(centralWidget);
        highDate->setObjectName(QStringLiteral("highDate"));

        horizontalLayout_2->addWidget(highDate);

        highMag = new QLabel(centralWidget);
        highMag->setObjectName(QStringLiteral("highMag"));

        horizontalLayout_2->addWidget(highMag);

        highLat = new QLabel(centralWidget);
        highLat->setObjectName(QStringLiteral("highLat"));

        horizontalLayout_2->addWidget(highLat);

        highLong = new QLabel(centralWidget);
        highLong->setObjectName(QStringLiteral("highLong"));

        horizontalLayout_2->addWidget(highLong);

        highDepth = new QLabel(centralWidget);
        highDepth->setObjectName(QStringLiteral("highDepth"));

        horizontalLayout_2->addWidget(highDepth);

        horizontalLayout_2->setStretch(0, 5);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 3);
        horizontalLayout_2->setStretch(3, 3);
        horizontalLayout_2->setStretch(4, 2);

        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout_3->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_3);

        horizontalLayout->setStretch(0, 3);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label1->setText(QApplication::translate("MainWindow", "Cutermur selectat:", Q_NULLPTR));
        highDate->setText(QApplication::translate("MainWindow", "data", Q_NULLPTR));
        highMag->setText(QApplication::translate("MainWindow", "magnitudine", Q_NULLPTR));
        highLat->setText(QApplication::translate("MainWindow", "latitudine", Q_NULLPTR));
        highLong->setText(QApplication::translate("MainWindow", "longitudine", Q_NULLPTR));
        highDepth->setText(QApplication::translate("MainWindow", "adancime", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
