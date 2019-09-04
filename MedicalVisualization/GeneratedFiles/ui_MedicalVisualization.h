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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MedicalVisualizationClass
{
public:
    QAction *actionFile_holes;
    QAction *actionReconstruction;
    QAction *actionShowHoles;
    QAction *actiondomainPoints;
    QAction *actionleafNodes;
    QWidget *centralWidget;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QMenu *menuFix;
    QMenu *menuPoints;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MedicalVisualizationClass)
    {
        if (MedicalVisualizationClass->objectName().isEmpty())
            MedicalVisualizationClass->setObjectName(QString::fromUtf8("MedicalVisualizationClass"));
        MedicalVisualizationClass->resize(869, 598);
        actionFile_holes = new QAction(MedicalVisualizationClass);
        actionFile_holes->setObjectName(QString::fromUtf8("actionFile_holes"));
        actionReconstruction = new QAction(MedicalVisualizationClass);
        actionReconstruction->setObjectName(QString::fromUtf8("actionReconstruction"));
        actionShowHoles = new QAction(MedicalVisualizationClass);
        actionShowHoles->setObjectName(QString::fromUtf8("actionShowHoles"));
        actiondomainPoints = new QAction(MedicalVisualizationClass);
        actiondomainPoints->setObjectName(QString::fromUtf8("actiondomainPoints"));
        actionleafNodes = new QAction(MedicalVisualizationClass);
        actionleafNodes->setObjectName(QString::fromUtf8("actionleafNodes"));
        centralWidget = new QWidget(MedicalVisualizationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(30, 30, 811, 491));
        MedicalVisualizationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MedicalVisualizationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 869, 26));
        menuFix = new QMenu(menuBar);
        menuFix->setObjectName(QString::fromUtf8("menuFix"));
        menuPoints = new QMenu(menuBar);
        menuPoints->setObjectName(QString::fromUtf8("menuPoints"));
        MedicalVisualizationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MedicalVisualizationClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MedicalVisualizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MedicalVisualizationClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MedicalVisualizationClass->setStatusBar(statusBar);

        menuBar->addAction(menuFix->menuAction());
        menuBar->addAction(menuPoints->menuAction());
        menuFix->addAction(actionFile_holes);
        menuFix->addAction(actionReconstruction);
        menuFix->addAction(actionShowHoles);
        menuPoints->addAction(actiondomainPoints);
        menuPoints->addAction(actionleafNodes);

        retranslateUi(MedicalVisualizationClass);
        QObject::connect(actionFile_holes, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(FillHoles()));
        QObject::connect(actionReconstruction, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(Reconstruction()));
        QObject::connect(actionShowHoles, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(ShowHoles()));
        QObject::connect(actiondomainPoints, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(DrawDomainPoints()));
        QObject::connect(actionleafNodes, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(DrawLeafNodes()));

        QMetaObject::connectSlotsByName(MedicalVisualizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *MedicalVisualizationClass)
    {
        MedicalVisualizationClass->setWindowTitle(QApplication::translate("MedicalVisualizationClass", "MedicalVisualization", nullptr));
        actionFile_holes->setText(QApplication::translate("MedicalVisualizationClass", "File holes", nullptr));
        actionReconstruction->setText(QApplication::translate("MedicalVisualizationClass", "Reconstruction", nullptr));
        actionShowHoles->setText(QApplication::translate("MedicalVisualizationClass", "ShowHolesModel", nullptr));
        actiondomainPoints->setText(QApplication::translate("MedicalVisualizationClass", "domainPoints", nullptr));
        actionleafNodes->setText(QApplication::translate("MedicalVisualizationClass", "leafNodes", nullptr));
        menuFix->setTitle(QApplication::translate("MedicalVisualizationClass", "Fix", nullptr));
        menuPoints->setTitle(QApplication::translate("MedicalVisualizationClass", "Points", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MedicalVisualizationClass: public Ui_MedicalVisualizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDICALVISUALIZATION_H
