/********************************************************************************
** Form generated from reading UI file 'Territory.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TERRITORY_H
#define UI_TERRITORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Territory
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_SearchPoint;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_N;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_affirm;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *Territory)
    {
        if (Territory->objectName().isEmpty())
            Territory->setObjectName(QString::fromUtf8("Territory"));
        Territory->resize(245, 99);
        widget = new QWidget(Territory);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(12, 11, 231, 81));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(28, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        lineEdit_SearchPoint = new QLineEdit(widget);
        lineEdit_SearchPoint->setObjectName(QString::fromUtf8("lineEdit_SearchPoint"));

        gridLayout->addWidget(lineEdit_SearchPoint, 0, 2, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        lineEdit_N = new QLineEdit(widget);
        lineEdit_N->setObjectName(QString::fromUtf8("lineEdit_N"));

        gridLayout->addWidget(lineEdit_N, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_affirm = new QPushButton(widget);
        pushButton_affirm->setObjectName(QString::fromUtf8("pushButton_affirm"));

        horizontalLayout_3->addWidget(pushButton_affirm);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_cancel = new QPushButton(widget);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout_3->addWidget(pushButton_cancel);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Territory);
        QObject::connect(pushButton_affirm, SIGNAL(clicked(bool)), Territory, SLOT(OnClickPushButtonAffirm()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked(bool)), Territory, SLOT(OnClickPushButtonCancel()));

        QMetaObject::connectSlotsByName(Territory);
    } // setupUi

    void retranslateUi(QWidget *Territory)
    {
        Territory->setWindowTitle(QApplication::translate("Territory", "Form", nullptr));
        label->setText(QApplication::translate("Territory", "\346\220\234\347\264\242\347\202\271\357\274\232", nullptr));
        label_2->setText(QApplication::translate("Territory", "N\351\230\266\351\242\206\345\237\237\357\274\232", nullptr));
        pushButton_affirm->setText(QApplication::translate("Territory", "\347\241\256\350\256\244", nullptr));
        pushButton_cancel->setText(QApplication::translate("Territory", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Territory: public Ui_Territory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERRITORY_H
