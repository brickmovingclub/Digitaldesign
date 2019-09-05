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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Territory
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_SearchPoint;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_N;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_affirm;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *Territory)
    {
        if (Territory->objectName().isEmpty())
            Territory->setObjectName(QString::fromUtf8("Territory"));
        Territory->resize(245, 99);
        layoutWidget = new QWidget(Territory);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 213, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lineEdit_SearchPoint = new QLineEdit(layoutWidget);
        lineEdit_SearchPoint->setObjectName(QString::fromUtf8("lineEdit_SearchPoint"));

        horizontalLayout->addWidget(lineEdit_SearchPoint);

        layoutWidget1 = new QWidget(Territory);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 40, 218, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        lineEdit_N = new QLineEdit(layoutWidget1);
        lineEdit_N->setObjectName(QString::fromUtf8("lineEdit_N"));

        horizontalLayout_2->addWidget(lineEdit_N);

        layoutWidget2 = new QWidget(Territory);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 70, 204, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_affirm = new QPushButton(layoutWidget2);
        pushButton_affirm->setObjectName(QString::fromUtf8("pushButton_affirm"));

        horizontalLayout_3->addWidget(pushButton_affirm);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_cancel = new QPushButton(layoutWidget2);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout_3->addWidget(pushButton_cancel);


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
