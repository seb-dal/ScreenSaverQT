#include "UI/screensaver.h"

#include <QApplication>
#include <QFrame>
#include <Widget/app_splashscreen.h>
#include <Widget/timerbutton_pushbutton.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Remember::initialize();
    TimerButton_PushButton::initialize();

    ScreenSaver w;
    APP_SplashScreen app_ss([&] { w.show(); });

    int err_code = app.exec();

    Remember::saveData();

    return err_code;
}
