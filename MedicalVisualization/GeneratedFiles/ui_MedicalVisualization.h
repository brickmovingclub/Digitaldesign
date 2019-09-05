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

QT_BEGIN_NAMESPACE

class Ui_MedicalVisualizationClass
{
public:
    QAction *actionFile_holes;
    QAction *actionReconstruction;
    QAction *actionShowHoles;
    QAction *actiondomainPoints;
    QAction *actionleafNodes;
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionSave_Project;
    QAction *actionExport;
    QAction *actionExit;
    QAction *actionImport;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFix;
    QMenu *menuPoints;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MedicalVisualizationClass)
    {
        if (MedicalVisualizationClass->objectName().isEmpty())
            MedicalVisualizationClass->setObjectName(QString::fromUtf8("MedicalVisualizationClass"));
        MedicalVisualizationClass->resize(868, 598);
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
        actionNew_Project = new QAction(MedicalVisualizationClass);
        actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
        actionOpen_Project = new QAction(MedicalVisualizationClass);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        actionSave_Project = new QAction(MedicalVisualizationClass);
        actionSave_Project->setObjectName(QString::fromUtf8("actionSave_Project"));
        actionExport = new QAction(MedicalVisualizationClass);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        actionExit = new QAction(MedicalVisualizationClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionImport = new QAction(MedicalVisualizationClass);
        actionImport->setObjectName(QString::fromUtf8("actionImport"));
        centralWidget = new QWidget(MedicalVisualizationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MedicalVisualizationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MedicalVisualizationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 868, 23));
        menuFix = new QMenu(menuBar);
        menuFix->setObjectName(QString::fromUtf8("menuFix"));
        menuPoints = new QMenu(menuBar);
        menuPoints->setObjectName(QString::fromUtf8("menuPoints"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MedicalVisualizationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MedicalVisualizationClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MedicalVisualizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MedicalVisualizationClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MedicalVisualizationClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuFix->menuAction());
        menuBar->addAction(menuPoints->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFix->addAction(actionFile_holes);
        menuFix->addAction(actionReconstruction);
        menuFix->addAction(actionShowHoles);
        menuPoints->addAction(actiondomainPoints);
        menuPoints->addAction(actionleafNodes);
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave_Project);
        menuFile->addAction(actionImport);
        menuFile->addAction(actionExport);
        menuFile->addAction(actionExit);

        retranslateUi(MedicalVisualizationClass);
        QObject::connect(actionFile_holes, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(FillHoles()));
        QObject::connect(actionReconstruction, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(Reconstruction()));
        QObject::connect(actionShowHoles, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(ShowHoles()));
        QObject::connect(actiondomainPoints, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(DrawDomainPoints()));
        QObject::connect(actionleafNodes, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(DrawLeafNodes()));
        QObject::connect(actionImport, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(ReadFile()));
        QObject::connect(actionExport, SIGNAL(triggered(bool)), MedicalVisualizationClass, SLOT(SaveFile()));

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
        actionNew_Project->setText(QApplication::translate("MedicalVisualizationClass", "New Project", nullptr));
        actionOpen_Project->setText(QApplication::translate("MedicalVisualizationClass", "Open Project", nullptr));
        actionSave_Project->setText(QApplication::translate("MedicalVisualizationClass", "Save Project", nullptr));
        actionExport->setText(QApplication::translate("MedicalVisualizationClass", "Export", nullptr));
        actionExit->setText(QApplication::translate("MedicalVisualizationClass", "Exit", nullptr));
        actionImport->setText(QApplication::translate("MedicalVisualizationClass", "Import", nullptr));
        menuFix->setTitle(QApplication::translate("MedicalVisualizationClass", "Fix", nullptr));
        menuPoints->setTitle(QApplication::translate("MedicalVisualizationClass", "Points", nullptr));
        menuFile->setTitle(QApplication::translate("MedicalVisualizationClass", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MedicalVisualizationClass", "Edit", nullptr));
        menuHelp->setTitle(QApplication::translate("MedicalVisualizationClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MedicalVisualizationClass: public Ui_MedicalVisualizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDICALVISUALIZATION_H
