/********************************************************************************
** Form generated from reading UI file 'vtkWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTKWIDGET_H
#define UI_VTKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_VtkWidget
{
public:
    QVTKWidget *qvtkWidget;

    void setupUi(QWidget *VtkWidget)
    {
        if (VtkWidget->objectName().isEmpty())
            VtkWidget->setObjectName(QString::fromUtf8("VtkWidget"));
        VtkWidget->resize(394, 300);
        qvtkWidget = new QVTKWidget(VtkWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(-10, 9, 411, 291));

        retranslateUi(VtkWidget);

        QMetaObject::connectSlotsByName(VtkWidget);
    } // setupUi

    void retranslateUi(QWidget *VtkWidget)
    {
        VtkWidget->setWindowTitle(QApplication::translate("VtkWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VtkWidget: public Ui_VtkWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTKWIDGET_H
