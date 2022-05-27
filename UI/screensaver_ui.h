#ifndef UI_SCREENSAVER_H
#define UI_SCREENSAVER_H

#include "../Widget/frameless.h"
#include "blackscreen.h"
#include "timerbutton.h"
#include "ui_template.h"
#include "utils/Remember_keys.h"
#include "utils/StyleLoader.h"
#include "utils/processesclearer.h"
#include "utils/remember.h"
#include <QApplication>
#include <QFrame>
#include <QMainWindow>
#include <QProcess>
#include <QPushButton>
#include <QtConcurrent>
#include <QtCore/QVariant>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScreenSaver {
public:
    QVBoxLayout* MainLayout;
    QFrame* frame;

    QVBoxLayout* secLayout;
    FrameLess* fl;

    TimerButton* veille;
    TimerButton* eteindre;
    TimerButton* ecranNoir;

    int nb;
    int time;
    bool hideAfter;

public:
    void setupUi(QMainWindow* ScreenSaver)
    {
        if (ScreenSaver->objectName().isEmpty())
            ScreenSaver->setObjectName(QString::fromUtf8("ScreenSaver"));
        ScreenSaver->setWindowTitle("ScreenSaver");

        QPoint pos = Remember::get_<QPoint>(App_Position::name(), QPoint(10, 10));
        ScreenSaver->move(pos);

        QSize size = Remember::get_<QSize>(App_Size::name(), QSize(200, 3 * 200));
        ScreenSaver->resize(size);

        StyleLoader::loadStyle(ScreenSaver, "://Style.css");
        {
            ScreenSaver->setWindowIcon(QIcon("://img/icon.png"));

            QPalette palette = ScreenSaver->palette();
            palette.setBrush(QPalette::Base, Qt::transparent);
            ScreenSaver->setWindowFlags(Qt::FramelessWindowHint);
            ScreenSaver->setAttribute(Qt::WA_NoSystemBackground);
            ScreenSaver->setAttribute(Qt::WA_TranslucentBackground);
            //widget->setAttribute(Qt::WA_TransparentForMouseEvents);
            ScreenSaver->setAttribute(Qt::WA_OpaquePaintEvent, false);

            fl = new FrameLess(ScreenSaver);
            ScreenSaver->setMinimumSize(100, 100);
        }

        componentCreate(frame, QFrame, ScreenSaver);
        {
            ScreenSaver->setCentralWidget(frame);
            frame->setFrameShape(QFrame::Shape::Box);
            frame->setFrameShadow(QFrame::Shadow::Raised);
            //ScreenSaver->setMidLineWidth(4);
            //ScreenSaver->setLineWidth(2);

            componentCreate(MainLayout, QVBoxLayout, frame);
            {
                MainLayout->setContentsMargins(0, 0, 0, 0);

                nb = Remember::get_(Number_After_Dot::name(), 1);
                nb = qMin(qMax(nb, 0), 2);
                Remember::put(Number_After_Dot::name(), nb);

                time = Remember::get_(Time_After_Button_Clicked::name(), 3);
                time = qMax(time, 0);
                Remember::put(Time_After_Button_Clicked::name(), time);

                hideAfter = Remember::get_(Hide_After_Action ::name(), 1) != 0;
                Remember::put(Hide_After_Action ::name(), hideAfter ? 1 : 0);

                component2Create(veille, TimerButton, ScreenSaver->tr("Mettre en veille"), frame);
                {
                    MainLayout->addWidget(veille);
                    veille->updateButton();
                    veille->setMaxTimer(time);
                    veille->setNumberAfterDot(static_cast<TimerButton_AFTER_DOT>(nb));
                    veille->setFunction([&] {
                        if (hideAfter) {
                            frame->parentWidget()->setWindowState(Qt::WindowMinimized);
                        }
                        QtConcurrent::run([] {
                            QString commande = "powershell.exe"
                                               " -command add-type"
                                               " -assemblyname System.Windows.Forms;"
                                               " [System.Windows.Forms.Application]::SetSuspendState([System.Windows.Forms.PowerState]::Suspend,"
                                               " $false, $false)";

                            QProcess* prog = new QProcess();
                            ProcessesClearer::add(prog);
                            prog->start("cmd", { "/c", commande });
                        });
                    });
                }

                component2Create(eteindre, TimerButton, "Eteindre l'écran", frame);
                {
                    MainLayout->addWidget(eteindre);
                    eteindre->updateButton();
                    eteindre->setMaxTimer(time);
                    eteindre->setNumberAfterDot(static_cast<TimerButton_AFTER_DOT>(nb));
                    eteindre->setFunction([&] {
                        if (hideAfter) {
                            frame->parentWidget()->setWindowState(Qt::WindowMinimized);
                        }
                        QtConcurrent::run([] {
                            QString commande = "(Add-Type '[DllImport(\"user32.dll\")]"
                                               " public static extern int SendMessage(int hWnd, "
                                               "int hMsg, int wParam, int lParam);"
                                               "' -Name a -Pas)::SendMessage(-1,0x0112,0xF170,2)";

                            QProcess* prog = new QProcess();
                            ProcessesClearer::add(prog);
                            prog->start("powershell", { commande });
                        });
                    });
                }

                component2Create(ecranNoir, TimerButton, "Ecran noire", frame);
                {
                    MainLayout->addWidget(ecranNoir);
                    ecranNoir->updateButton();
                    ecranNoir->setMaxTimer(time);
                    ecranNoir->setNumberAfterDot(static_cast<TimerButton_AFTER_DOT>(nb));
                    ecranNoir->setFunction([&] {
                        if (hideAfter) {
                            frame->parentWidget()->setWindowState(Qt::WindowMinimized);
                        }
                        BlackScreen screen;
                        screen.show();
                        screen.exec();
                    });
                }
            }
        }

        retranslateUi(ScreenSaver);

        QMetaObject::connectSlotsByName(ScreenSaver);
    } // setupUi

    void
    retranslateUi(QMainWindow* ScreenSaver)
    {
        ScreenSaver->setWindowTitle("ScreenSaver");
    } // retranslateUi
};

Ui_decl(ScreenSaver);

QT_END_NAMESPACE

#endif // UI_SCREENSAVER_H
