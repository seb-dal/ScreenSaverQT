#include "app_splashscreen.h"

#define deleteIF(var)  \
    if (var) {         \
        delete var;    \
        var = nullptr; \
    }

APP_SplashScreen::APP_SplashScreen(std::function<void()> func_then, const int time)
    : time(time)
    , func_then(func_then)
{
    QPixmap pixmap("://img/splash.png");

    splash = new QSplashScreen(pixmap);
    opacity = new QGraphicsOpacityEffect(splash);
    splash->setGraphicsEffect(opacity);
    fadeAnimation = new QPropertyAnimation(opacity, "opacity");
    fadeAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    fadeIn();
    splash->show();
}

APP_SplashScreen::~APP_SplashScreen()
{
    deleteIF(splash);
    deleteIF(fadeAnimation);
}

void APP_SplashScreen::fadeIn()
{
    fadeAnimation->setStartValue(0.01);
    fadeAnimation->setEndValue(1.0);
    fadeAnimation->setDuration(time);

    fadeAnimation->start(QAbstractAnimation::KeepWhenStopped);
    QTimer::singleShot(time, this, SLOT(fadeOut()));
}

void APP_SplashScreen::fadeOut()
{
    fadeAnimation->stop();
    fadeAnimation->setStartValue(1.0);
    fadeAnimation->setEndValue(0.01);
    fadeAnimation->setDuration(time);

    fadeAnimation->start(QAbstractAnimation::KeepWhenStopped);
    QTimer::singleShot(time, this, SLOT(hide()));
}

void APP_SplashScreen::hide()
{
    fadeAnimation->stop();
    func_then();
    splash->hide();
    deleteIF(splash);
    deleteIF(fadeAnimation);
}
