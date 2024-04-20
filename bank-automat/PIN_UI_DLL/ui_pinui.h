/********************************************************************************
** Form generated from reading UI file 'pinui.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PINUI_H
#define UI_PINUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pinUI
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *btn_1;
    QPushButton *btn_2;
    QPushButton *btn_3;
    QPushButton *btn_4;
    QPushButton *btn_5;
    QPushButton *btn_6;
    QPushButton *btn_7;
    QPushButton *btn_8;
    QPushButton *btn_9;
    QPushButton *btn_clear;
    QPushButton *btn_0;
    QPushButton *pushButton;

    void setupUi(QDialog *pinUI)
    {
        if (pinUI->objectName().isEmpty())
            pinUI->setObjectName("pinUI");
        pinUI->resize(366, 349);
        layoutWidget = new QWidget(pinUI);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(40, 10, 291, 211));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);
        label->setFrameShape(QFrame::Box);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 1, 0, 1, 3);

        btn_1 = new QPushButton(layoutWidget);
        btn_1->setObjectName("btn_1");

        gridLayout->addWidget(btn_1, 2, 0, 1, 1);

        btn_2 = new QPushButton(layoutWidget);
        btn_2->setObjectName("btn_2");

        gridLayout->addWidget(btn_2, 2, 1, 1, 1);

        btn_3 = new QPushButton(layoutWidget);
        btn_3->setObjectName("btn_3");

        gridLayout->addWidget(btn_3, 2, 2, 1, 1);

        btn_4 = new QPushButton(layoutWidget);
        btn_4->setObjectName("btn_4");

        gridLayout->addWidget(btn_4, 3, 0, 1, 1);

        btn_5 = new QPushButton(layoutWidget);
        btn_5->setObjectName("btn_5");

        gridLayout->addWidget(btn_5, 3, 1, 1, 1);

        btn_6 = new QPushButton(layoutWidget);
        btn_6->setObjectName("btn_6");

        gridLayout->addWidget(btn_6, 3, 2, 1, 1);

        btn_7 = new QPushButton(layoutWidget);
        btn_7->setObjectName("btn_7");

        gridLayout->addWidget(btn_7, 4, 0, 1, 1);

        btn_8 = new QPushButton(layoutWidget);
        btn_8->setObjectName("btn_8");

        gridLayout->addWidget(btn_8, 4, 1, 1, 1);

        btn_9 = new QPushButton(layoutWidget);
        btn_9->setObjectName("btn_9");

        gridLayout->addWidget(btn_9, 4, 2, 1, 1);

        btn_clear = new QPushButton(layoutWidget);
        btn_clear->setObjectName("btn_clear");

        gridLayout->addWidget(btn_clear, 5, 0, 1, 1);

        btn_0 = new QPushButton(layoutWidget);
        btn_0->setObjectName("btn_0");

        gridLayout->addWidget(btn_0, 5, 1, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 5, 2, 1, 1);


        retranslateUi(pinUI);

        QMetaObject::connectSlotsByName(pinUI);
    } // setupUi

    void retranslateUi(QDialog *pinUI)
    {
        pinUI->setWindowTitle(QCoreApplication::translate("pinUI", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("pinUI", "Sy\303\266t\303\244 PIN", nullptr));
        btn_1->setText(QCoreApplication::translate("pinUI", "1", nullptr));
        btn_2->setText(QCoreApplication::translate("pinUI", "2", nullptr));
        btn_3->setText(QCoreApplication::translate("pinUI", "3", nullptr));
        btn_4->setText(QCoreApplication::translate("pinUI", "4", nullptr));
        btn_5->setText(QCoreApplication::translate("pinUI", "5", nullptr));
        btn_6->setText(QCoreApplication::translate("pinUI", "6", nullptr));
        btn_7->setText(QCoreApplication::translate("pinUI", "7", nullptr));
        btn_8->setText(QCoreApplication::translate("pinUI", "8", nullptr));
        btn_9->setText(QCoreApplication::translate("pinUI", "9", nullptr));
        btn_clear->setText(QCoreApplication::translate("pinUI", "Clear", nullptr));
        btn_0->setText(QCoreApplication::translate("pinUI", "0", nullptr));
        pushButton->setText(QCoreApplication::translate("pinUI", "Enter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pinUI: public Ui_pinUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PINUI_H
