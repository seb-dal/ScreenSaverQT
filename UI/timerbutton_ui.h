#ifndef UI_SCREENSAVER_H
#define UI_SCREENSAVER_H

#include "Widget/timerbutton_pushbutton.h"
#include "ui_template.h"
#include "utils/StyleLoader.h"
#include "utils/appConst.h"
#include "utils/util.h"
#include <QTabWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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

        parent->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

        componentCreate(MainLayout, QVBoxLayout, parent);
        {
            MainLayout->setContentsMargins(0, appConst::spaceBetweenButton, 0, appConst::spaceBetweenButton);
            componentCreate(horizontalLayout, QHBoxLayout, nullptr);
            {
                horizontalLayout->setContentsMargins(0, 0, 0, 0);
                MainLayout->addLayout(horizontalLayout);

                componentCreate(Title, QLabel, parent);
                {
                    horizontalLayout->addWidget(Title);

                    Title->setAlignment(Qt::AlignCenter);
                    Title->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred));

                    util::setFontBold(Title, true);
                }

                componentCreate(bt, TimerButton_PushButton, parent);
                {
                    MainLayout->addWidget(bt);
                    bt->setContentsMargins(0, 0, 0, 0);
                }
            }
        }
        QMetaObject::connectSlotsByName(parent);
    } // setupUi

    void
    retranslateUi(QWidget* /*parent*/)
    {
    } // retranslateUi
};

Ui_decl(TimerButton);

QT_END_NAMESPACE

#endif // UI_SCREENSAVER_H
