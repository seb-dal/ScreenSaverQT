#ifndef DIALBUTTON_UI_H
#define DIALBUTTON_UI_H

#include "ui_template.h"
#include "utils/appConst.h"
#include "utils/util.h"

#include <QDial>
#include <QLabel>
#include <QTabWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialButton {
public:
    QVBoxLayout* MainLayout = nullptr;
    QHBoxLayout* horizontalLayout = nullptr;
    QLabel* Title = nullptr;
    QDial* bt = nullptr;

    QVBoxLayout* InLayout = nullptr;
    QLabel* content = nullptr;

public:
    void setupUi(QWidget* parent)
    {
        if (parent->objectName().isEmpty())
            parent->setObjectName(QString::fromUtf8("DialButton"));

        parent->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

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

                componentCreate(bt, QDial, parent);
                {
                    MainLayout->addWidget(bt);
                    bt->setContentsMargins(0, 0, 0, 0);
                    bt->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

                    bt->setMaximum(220 - 1);
                    bt->setMinimum(0);
                    QObject::connect(bt, SIGNAL(valueChanged(int)), parent, SLOT(value(int)));

                    componentCreate(InLayout, QVBoxLayout, bt);
                    {
                        bt->setLayout(InLayout);
                        InLayout->setContentsMargins(0, 0, 0, 0);

                        componentCreate(content, QLabel, bt);
                        {
                            InLayout->addWidget(content);
                            content->setFont(QFont("Arial"));

                            content->setAlignment(Qt::AlignCenter);
                            content->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

                            util::setFontBold(content, true);

                            QObject::connect(bt, SIGNAL(valueChanged(int)), parent, SLOT(textUpdate(int)));
                        }
                    }
                }
            }
        }

        QMetaObject::connectSlotsByName(parent);
    } // setupUi

    void retranslateUi(QWidget* /*parent*/)
    {
    } // retranslateUi
};

Ui_decl(DialButton);

QT_END_NAMESPACE

#endif // DIALBUTTON_UI_H
