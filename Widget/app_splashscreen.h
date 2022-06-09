#ifndef APP_SPLASHSCREEN_H
#define APP_SPLASHSCREEN_H

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSplashScreen>
#include <QTimer>

class APP_SplashScreen : public QObject {
    Q_OBJECT
public:
    APP_SplashScreen(QObject* parent = nullptr);
    APP_SplashScreen(std::function<void()> func_then, const int time = 500);

    ~APP_SplashScreen();

public slots:

    void fadeIn();
    void fadeOut();

    void hide();

private:
    int time;
    std::function<void()> func_then;
    QSplashScreen* splash = nullptr;
    QGraphicsOpacityEffect* opacity = nullptr;
    QPropertyAnimation* fadeAnimation = nullptr;
};

#endif // APP_SPLASHSCREEN_H
