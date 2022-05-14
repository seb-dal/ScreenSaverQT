#ifndef UI_SCREENSAVER_H
#define UI_SCREENSAVER_H

#include "ui_template.h"

#include <QTabWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <Widget/timerbutton_pushbutton.h>
#include <utils/StyleLoader.h>

QT_BEGIN_NAMESPACE

class Ui_TimerButton {
public:
    QVBoxLayout* MainLayout;
    QHBoxLayout* horizontalLayout;
    QLabel* Title;
    TimerButton_PushButton* bt;

public:
    void setupUi(QWidget* parent)
    {
        if (parent->objectName().isEmpty())
            parent->setObjectName(QString::fromUtf8("timerButton"));

        componentCreate(MainLayout, QVBoxLayout, parent);
        {
            componentCreate(horizontalLayout, QHBoxLayout, nullptr);
            {
                MainLayout->addLayout(horizontalLayout);

                componentCreate(Title, QLabel, parent);
                {
                    horizontalLayout->addWidget(Title);
                    Title->setAlignment(Qt::AlignCenter);
                    Title->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred));

                    componentCreate(bt, TimerButton_PushButton, Title);
                    {
                        MainLayout->addWidget(bt);
                    }
                }
            }
        }
        QMetaObject::connectSlotsByName(parent);
    } // setupUi

    void
    retranslateUi(QWidget* parent)
    {
    } // retranslateUi
};

Ui_decl(TimerButton);

QT_END_NAMESPACE

#endif // UI_SCREENSAVER_H
