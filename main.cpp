#include "UI/screensaver.h"

#include "Widget/app_splashscreen.h"
#include "Widget/timerbutton_pushbutton.h"
#include "utils/processesclearer.h"
#include "utils/translator.h"
#include <QApplication>
#include <QFrame>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Remember::initialize();
    Translator::setLanguage();

    TimerButton_PushButton::initialize();

    ScreenSaver w;
    APP_SplashScreen app_ss([&] { w.show(); });

    int err_code = app.exec();

    Remember::saveData();
    ProcessesClearer::clearAll();

    return err_code;
}
