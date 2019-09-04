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
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionSave_Project;
    QAction *actionSave_Project_As;
    QAction *actionExport;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionPast;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuFix;
    QMenu *menuSurface;
    QMenu *menuOption;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MedicalVisualizationClass)
    {
        if (MedicalVisualizationClass->objectName().isEmpty())
            MedicalVisualizationClass->setObjectName(QString::fromUtf8("MedicalVisualizationClass"));
        MedicalVisualizationClass->resize(951, 580);
        actionNew_Project = new QAction(MedicalVisualizationClass);
        actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
        actionOpen_Project = new QAction(MedicalVisualizationClass);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        actionSave_Project = new QAction(MedicalVisualizationClass);
        actionSave_Project->setObjectName(QString::fromUtf8("actionSave_Project"));
        actionSave_Project_As = new QAction(MedicalVisualizationClass);
        actionSave_Project_As->setObjectName(QString::fromUtf8("actionSave_Project_As"));
        actionExport = new QAction(MedicalVisualizationClass);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        actionUndo = new QAction(MedicalVisualizationClass);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedo = new QAction(MedicalVisualizationClass);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionPast = new QAction(MedicalVisualizationClass);
        actionPast->setObjectName(QString::fromUtf8("actionPast"));
        centralWidget = new QWidget(MedicalVisualizationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MedicalVisualizationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MedicalVisualizationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 951, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuFix = new QMenu(menuBar);
        menuFix->setObjectName(QString::fromUtf8("menuFix"));
        menuSurface = new QMenu(menuBar);
        menuSurface->setObjectName(QString::fromUtf8("menuSurface"));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QString::fromUtf8("menuOption"));
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
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuFix->menuAction());
        menuBar->addAction(menuSurface->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_Project_As);
        menuFile->addAction(actionExport);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addAction(actionPast);

        retranslateUi(MedicalVisualizationClass);

        QMetaObject::connectSlotsByName(MedicalVisualizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *MedicalVisualizationClass)
    {
        MedicalVisualizationClass->setWindowTitle(QApplication::translate("MedicalVisualizationClass", "MedicalVisualization", nullptr));
        actionNew_Project->setText(QApplication::translate("MedicalVisualizationClass", "New Project", nullptr));
        actionOpen_Project->setText(QApplication::translate("MedicalVisualizationClass", "Open Project", nullptr));
        actionSave_Project->setText(QApplication::translate("MedicalVisualizationClass", "Save Project", nullptr));
        actionSave_Project_As->setText(QApplication::translate("MedicalVisualizationClass", "Save Project As", nullptr));
        actionExport->setText(QApplication::translate("MedicalVisualizationClass", "Export", nullptr));
        actionUndo->setText(QApplication::translate("MedicalVisualizationClass", "Undo", nullptr));
        actionRedo->setText(QApplication::translate("MedicalVisualizationClass", "Redo", nullptr));
        actionPast->setText(QApplication::translate("MedicalVisualizationClass", "Past", nullptr));
        menuFile->setTitle(QApplication::translate("MedicalVisualizationClass", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MedicalVisualizationClass", "Edit", nullptr));
        menuView->setTitle(QApplication::translate("MedicalVisualizationClass", "View", nullptr));
        menuFix->setTitle(QApplication::translate("MedicalVisualizationClass", "Fix", nullptr));
        menuSurface->setTitle(QApplication::translate("MedicalVisualizationClass", "Surface", nullptr));
        menuOption->setTitle(QApplication::translate("MedicalVisualizationClass", "Option", nullptr));
        menuHelp->setTitle(QApplication::translate("MedicalVisualizationClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MedicalVisualizationClass: public Ui_MedicalVisualizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDICALVISUALIZATION_H
