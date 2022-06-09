#include "UI/screensaver.h"

#include "Widget/app_splashscreen.h"
#include "Widget/timerbutton_pushbutton.h"
#include "utils/processesclearer.h"
#include "utils/translator.h"
#include <QApplication>
#include <QFrame>

int main(int argc, char* argv[])
{
    int err_code = 0;
    bool firstShow = true;

    while (ScreenSaver::reboot) {

        ScreenSaver::reboot = false;
        QApplication app(argc, argv);

        Remember::initialize();

        Translator::setLanguage();

        TimerButton_PushButton::initialize();

        ScreenSaver w;

        if (firstShow) {
            APP_SplashScreen app_ss([&] { w.show(); });
            firstShow = false;

            err_code = app.exec();
        } else {
            w.show();

            err_code = app.exec();
        }

        Remember::saveData();
        ProcessesClearer::clearAll();
        TimerButton_PushButton::deleteStatic();
        Translator::free();
    }

    return err_code;
}
