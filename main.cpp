#include "UI/screensaver.h"

#include "Widget/app_splashscreen.h"
#include "Widget/timerbutton_pushbutton.h"
#include "utils/Remember_keys.h"
#include "utils/processesclearer.h"
#include "utils/translator.h"

#include <QApplication>
#include <QFrame>
#include <QScreen>

int main(int argc, char* argv[])
{
    int err_code = 0;
    bool firstShow = true;

    do {

        ScreenSaver::reboot = false;
        QApplication app(argc, argv);

        Remember::initialize();

        QString lang = Remember::get_(APP::Language::name(), QString("en"));
        Translator::setLanguage(lang);

        TimerButton_PushButton::initialize();

        ScreenSaver w;

        QObject::connect(&app, &QApplication::screenAdded, &w, &ScreenSaver::rebootApp);
        QObject::connect(&app, &QApplication::screenRemoved, &w, &ScreenSaver::rebootApp);

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
    } while (ScreenSaver::reboot);

    return err_code;
}
