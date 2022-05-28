#ifndef DIALBUTTON_UI_H
#define DIALBUTTON_UI_H

#include "ui_template.h"

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

        componentCreate(MainLayout, QVBoxLayout, parent);
        {
            MainLayout->setContentsMargins(0, 6, 0, 6);
            componentCreate(horizontalLayout, QHBoxLayout, nullptr);
            {
                horizontalLayout->setContentsMargins(0, 0, 0, 0);
                MainLayout->addLayout(horizontalLayout);

                componentCreate(Title, QLabel, parent);
                {
                    horizontalLayout->addWidget(Title);
                    Title->setAlignment(Qt::AlignCenter);
                    Title->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred));

                    QFont f(Title->font());
                    {
                        f.setBold(true);
                    }
                    Title->setFont(f);

                    componentCreate(bt, QDial, Title);
                    {
                        MainLayout->addWidget(bt);

                        bt->setMaximum(200);
                        bt->setMinimum(0);

                        componentCreate(InLayout, QVBoxLayout, bt);
                        {
                            bt->setLayout(InLayout);
                            InLayout->setContentsMargins(0, 0, 0, 0);

                            componentCreate(content, QLabel, bt);
                            {
                                InLayout->addWidget(content);
                                content->setAlignment(Qt::AlignCenter);
                                content->setSizePolicy(
                                    QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
                                QFont f(content->font());
                                {
                                    f.setBold(true);
                                    content->setFont(f);
                                }

                                QObject::connect(bt, &QDial::valueChanged, [&](int n) {
                                    float min = bt->minimum();
                                    float max = bt->maximum();
                                    float f = (n - min) / (max - min);
                                    content->setText(QString("%1%").arg((int)(f * 100)));
                                });
                                content->setText("0%");
                            }
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
