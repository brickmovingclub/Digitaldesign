/********************************************************************************
** Form generated from reading UI file 'MedicalVisualization.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDICALVISUALIZATION_H
#define UI_MEDICALVISUALIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MedicalVisualizationClass
{
public:
    QWidget *centralWidget;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MedicalVisualizationClass)
    {
        if (MedicalVisualizationClass->objectName().isEmpty())
            MedicalVisualizationClass->setObjectName(QString::fromUtf8("MedicalVisualizationClass"));
        MedicalVisualizationClass->resize(588, 400);
        centralWidget = new QWidget(MedicalVisualizationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(140, 110, 401, 211));
        MedicalVisualizationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MedicalVisualizationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 588, 23));
        MedicalVisualizationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MedicalVisualizationClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MedicalVisualizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MedicalVisualizationClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MedicalVisualizationClass->setStatusBar(statusBar);

        retranslateUi(MedicalVisualizationClass);

        QMetaObject::connectSlotsByName(MedicalVisualizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *MedicalVisualizationClass)
    {
        MedicalVisualizationClass->setWindowTitle(QApplication::translate("MedicalVisualizationClass", "MedicalVisualization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MedicalVisualizationClass: public Ui_MedicalVisualizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDICALVISUALIZATION_H
