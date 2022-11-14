/********************************************************************************
** Form generated from reading UI file 'WindowTelemetryView.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWTELEMETRYVIEW_H
#define UI_WINDOWTELEMETRYVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowTelemetryView
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *WindowTelemetryView)
    {
        if (WindowTelemetryView->objectName().isEmpty())
            WindowTelemetryView->setObjectName(QString::fromUtf8("WindowTelemetryView"));
        WindowTelemetryView->resize(961, 638);
        verticalLayoutWidget = new QWidget(WindowTelemetryView);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 931, 601));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(WindowTelemetryView);

        QMetaObject::connectSlotsByName(WindowTelemetryView);
    } // setupUi

    void retranslateUi(QDialog *WindowTelemetryView)
    {
        WindowTelemetryView->setWindowTitle(QCoreApplication::translate("WindowTelemetryView", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowTelemetryView: public Ui_WindowTelemetryView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWTELEMETRYVIEW_H
