#ifndef UI_SCREENSAVER_H
#define UI_SCREENSAVER_H

#include "UI/dialbutton.h"
#include "Widget/frameless.h"
#include "blackscreen.h"
#include "semitransparentscreen.h"
#include "timerbutton.h"
#include "ui_template.h"
#include "utils/Remember_keys.h"
#include "utils/StyleLoader.h"
#include "utils/processesclearer.h"
#include "utils/remember.h"
#include <QApplication>
#include <QDial>
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

    FrameLess* fl;

    TimerButton* veille;
    TimerButton* eteindre;
    TimerButton* ecranNoir;

    DialButton* dial_semiTransparentScreen;
    SemiTransparentScreen* sts;

    bool hideAfter;

public:
    void setupUi(QMainWindow* ScreenSaver)
    {
        if (ScreenSaver->objectName().isEmpty())
            ScreenSaver->setObjectName(QString::fromUtf8("ScreenSaver"));
        ScreenSaver->setWindowTitle("ScreenSaver");

        int nb = Remember::get_(APP::Number_After_Dot::name(), 1);
        nb = qMin(qMax(nb, 0), 2);
        Remember::put(APP::Number_After_Dot::name(), nb);

        int time = Remember::get_(APP::Time_After_Button_Clicked::name(), 3);
        time = qMax(time, 0);
        Remember::put(APP::Time_After_Button_Clicked::name(), time);

        hideAfter = Remember::get_(APP::Hide_After_Action ::name(), 1) != 0;

        bool veille_display = Remember::get_(APP::Show_Standby_Button::name(), 1) != 0;

        bool eteindre_display = Remember::get_(APP::Show_ScreenOff_Button::name(), 1) != 0;

        bool ecranNoir_display = Remember::get_(APP::Show_BlackScreen_Button::name(), 1) != 0;

        bool sts_display = Remember::get_(APP::Show_ShadeScreen_Button::name(), 1) != 0;

        QPoint pos = Remember::get_<QPoint>(APP::App_Position::name(), QPoint(10, 10));
        ScreenSaver->move(pos);

        int nbButton
            = static_cast<int>(veille_display)
            + static_cast<int>(eteindre_display)
            + static_cast<int>(ecranNoir_display)
            + static_cast<int>(sts_display);

        QSize size = Remember::get_<QSize>(APP::App_Size::name(), QSize(200, nbButton * 200));
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
            ScreenSaver->setMinimumSize(100, nbButton * 75);
        }

        componentCreate(frame, QFrame, ScreenSaver);
        {
            ScreenSaver->setCentralWidget(frame);
            frame->setFrameShape(QFrame::Shape::Box);
            frame->setFrameShadow(QFrame::Shadow::Raised);

            componentCreate(MainLayout, QVBoxLayout, frame);
            {
                MainLayout->setContentsMargins(0, 0, 0, 0);

                if (veille_display) {
                    component2Create(veille, TimerButton, QCoreApplication::translate("ScreenSaver", "Standby"), frame);
                    {
                        MainLayout->addWidget(veille);
                        veille->updateButton();
                        veille->setMaxTimer(time);
                        veille->setNumberAfterDot(static_cast<TimerButton_AFTER_DOT>(nb));
                        veille->setFunction([this] {
                            if (hideAfter) {
                                frame->parentWidget()->setWindowState(Qt::WindowMinimized);
                            }
                            auto ret = QtConcurrent::run([] {
                                bool hibernateMode = Remember::get_(APP::Standby_HibernateMode::name(), 1) != 0;

                                QString commande = QString(
                                    "powershell.exe"
                                    " -command add-type"
                                    " -assemblyname System.Windows.Forms;"
                                    " [System.Windows.Forms.Application]::SetSuspendState("
                                    "[System.Windows.Forms.PowerState]::%1, $false, $false)")
                                                       .arg(hibernateMode ? "Hibernate" : "Suspend");

                                QProcess* prog = new QProcess();
                                ProcessesClearer::add(prog);
                                prog->start("cmd", { "/c", commande });
                            });
                        });
                    }
                }

                if (eteindre_display) {
                    component2Create(eteindre, TimerButton, QCoreApplication::translate("ScreenSaver", "Turn off screen"), frame);
                    {
                        MainLayout->addWidget(eteindre);
                        eteindre->updateButton();
                        eteindre->setMaxTimer(time);
                        eteindre->setNumberAfterDot(static_cast<TimerButton_AFTER_DOT>(nb));
                        eteindre->setFunction([this] {
                            if (hideAfter) {
                                frame->parentWidget()->setWindowState(Qt::WindowMinimized);
                            }
                            auto ret = QtConcurrent::run([] {
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
                }

                if (ecranNoir_display) {
                    component2Create(ecranNoir, TimerButton, QCoreApplication::translate("ScreenSaver", "Black Screen"), frame);
                    {
                        MainLayout->addWidget(ecranNoir);
                        ecranNoir->updateButton();
                        ecranNoir->setMaxTimer(time);
                        ecranNoir->setNumberAfterDot(static_cast<TimerButton_AFTER_DOT>(nb));
                        ecranNoir->setFunction([this] {
                            if (hideAfter) {
                                frame->parentWidget()->setWindowState(Qt::WindowMinimized);
                            }
                            BlackScreen screen;
                            screen.show();
                            screen.exec();
                        });
                    }
                }

                if (sts_display) {
                    component2Create(dial_semiTransparentScreen, DialButton, QCoreApplication::translate("ScreenSaver", "Opacity"), frame);
                    {
                        MainLayout->addWidget(dial_semiTransparentScreen);

                        componentCreate(sts, SemiTransparentScreen, nullptr);
                        {
                            sts->show();
                            QObject::connect( //
                                dial_semiTransparentScreen,
                                &DialButton::valueChange,
                                sts,
                                &SemiTransparentScreen::setTransparenty);
                        }
                    }
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
