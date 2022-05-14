#ifndef UI_SCREENSAVER_H
#define UI_SCREENSAVER_H

#include "../Widget/frameless.h"
#include "timerbutton.h"
#include "ui_template.h"

#include <QFrame>
#include <QPushButton>
#include <QtCore/QVariant>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <utils/StyleLoader.h>

QT_BEGIN_NAMESPACE

class Ui_ScreenSaver {
public:
    QVBoxLayout* MainLayout;
    FrameLess* fl;
    QPushButton* quit;
    QPushButton* reduce;

    TimerButton* test;

public:
    void setupUi(QFrame* ScreenSaver)
    {
        if (ScreenSaver->objectName().isEmpty())
            ScreenSaver->setObjectName(QString::fromUtf8("ScreenSaver"));
        ScreenSaver->setWindowTitle("ScreenSaver");
        ScreenSaver->resize(501, 295);
        ScreenSaver->setObjectName(QString::fromUtf8("centralwidget"));

        StyleLoader::loadStyle(ScreenSaver, "://Style.css");
        {
            ScreenSaver->setWindowIcon(QIcon("://img/icon.png"));

            ScreenSaver->setFrameShape(QFrame::Shape::Box);
            ScreenSaver->setFrameShadow(QFrame::Shadow::Raised);
            ScreenSaver->setMidLineWidth(4);
            ScreenSaver->setLineWidth(2);
            QPalette palette = ScreenSaver->palette();
            palette.setBrush(QPalette::Base, Qt::transparent);
            ScreenSaver->setWindowFlags(Qt::FramelessWindowHint);
            ScreenSaver->setAttribute(Qt::WA_NoSystemBackground);
            ScreenSaver->setAttribute(Qt::WA_TranslucentBackground);
            //widget->setAttribute(Qt::WA_TransparentForMouseEvents);
            ScreenSaver->setAttribute(Qt::WA_OpaquePaintEvent, false);

            fl = new FrameLess(ScreenSaver);
            ScreenSaver->setMinimumSize(200, 200);
        }

        componentCreate(MainLayout, QVBoxLayout, ScreenSaver);
        {
            component2Create(test, TimerButton, "TEST", ScreenSaver);
            {
                MainLayout->addWidget(test);
                test->updateButton();
                test->setNumberAfterDot(ONE);
            }
        }

        retranslateUi(ScreenSaver);

        QMetaObject::connectSlotsByName(ScreenSaver);
    } // setupUi

    void retranslateUi(QFrame* ScreenSaver)
    {
        ScreenSaver->setWindowTitle("ScreenSaver");
    } // retranslateUi
};

Ui_decl(ScreenSaver);

QT_END_NAMESPACE

#endif // UI_SCREENSAVER_H
