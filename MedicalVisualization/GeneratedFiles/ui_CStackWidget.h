/********************************************************************************
** Form generated from reading UI file 'CStackWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSTACKWIDGET_H
#define UI_CSTACKWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StackWidget
{
public:

    void setupUi(QWidget *StackWidget)
    {
        if (StackWidget->objectName().isEmpty())
            StackWidget->setObjectName(QString::fromUtf8("StackWidget"));
        StackWidget->resize(400, 300);

        retranslateUi(StackWidget);

        QMetaObject::connectSlotsByName(StackWidget);
    } // setupUi

    void retranslateUi(QWidget *StackWidget)
    {
        StackWidget->setWindowTitle(QApplication::translate("StackWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StackWidget: public Ui_StackWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSTACKWIDGET_H
