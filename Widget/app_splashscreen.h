#ifndef APP_SPLASHSCREEN_H
#define APP_SPLASHSCREEN_H

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSplashScreen>
#include <QTimer>

class APP_SplashScreen : public QObject {
    Q_OBJECT
public:
    APP_SplashScreen(std::function<void()> func_then)
        : func_then(func_then)
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

#define deleteIF(var)  \
    if (var) {         \
        delete var;    \
        var = nullptr; \
    }

    ~APP_SplashScreen()
    {
        deleteIF(splash);
        deleteIF(fadeAnimation);
    }

public slots:

    void fadeIn()
    {
        fadeAnimation->setStartValue(0.01);
        fadeAnimation->setEndValue(1.0);
        fadeAnimation->setDuration(time);

        fadeAnimation->start(QAbstractAnimation::KeepWhenStopped);
        QTimer::singleShot(time, this, SLOT(fadeOut()));
    }
    void fadeOut()
    {
        fadeAnimation->stop();
        fadeAnimation->setStartValue(1.0);
        fadeAnimation->setEndValue(0.01);
        fadeAnimation->setDuration(time);

        fadeAnimation->start(QAbstractAnimation::KeepWhenStopped);
        QTimer::singleShot(time, this, SLOT(hide()));
    }

    void hide()
    {
        fadeAnimation->stop();
        func_then();
        splash->hide();
        deleteIF(splash);
        deleteIF(fadeAnimation);
    }

private:
    const int time = 500;
    std::function<void()> func_then;
    QSplashScreen* splash = nullptr;
    QGraphicsOpacityEffect* opacity = nullptr;
    QPropertyAnimation* fadeAnimation = nullptr;
};

#endif // APP_SPLASHSCREEN_H
