#include "UI/screensaver.h"

#include <QApplication>
#include <QFrame>
#include <Widget/app_splashscreen.h>
#include <Widget/timerbutton_pushbutton.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    TimerButton_PushButton::initialize();

    ScreenSaver w;
    APP_SplashScreen app_ss([&] {
        w.show();
    });

    //app.processEvents();

    return app.exec();

    /*QApplication a(argc, argv);
    QFrame *widget = new QFrame;
    widget->setFrameShape( QFrame::Shape::Box);
    widget->setLineWidth(8);
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Base, Qt::transparent);
    widget->setWindowFlags(Qt::FramelessWindowHint);
    widget->setAttribute(Qt::WA_NoSystemBackground);
    widget->setAttribute(Qt::WA_TranslucentBackground);
    //widget->setAttribute(Qt::WA_TransparentForMouseEvents);
    widget->setAttribute(Qt::WA_OpaquePaintEvent, false);
    FrameLess f(widget);
    widget->show();
    return a.exec();*/
}
