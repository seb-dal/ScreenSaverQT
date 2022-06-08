#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include "utils/remember.h"
#include <QMainWindow>
#include <QProcess>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class ScreenSaver;
}

QT_END_NAMESPACE

class ScreenSaver : public QMainWindow {
    Q_OBJECT

public:
    ScreenSaver(QWidget* parent = nullptr);
    ~ScreenSaver();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void ShowHideframe();
    bool event(QEvent* e) override;

private:
    bool show_frame = false;

public:
    static bool reboot;

private:
    Ui::ScreenSaver* ui;
};
#endif // SCREENSAVER_H
