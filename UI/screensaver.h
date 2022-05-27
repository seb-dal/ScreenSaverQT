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
namespace Var {
struct ScreenSaver {
    bool show_frame = false;
};
}

QT_END_NAMESPACE

class ScreenSaver : public QMainWindow {
    Q_OBJECT

public:
    ScreenSaver(QWidget* parent = nullptr);
    ~ScreenSaver();

    void hide_win()
    {
        this->hide();
    }

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void ShowHideframe();
    bool event(QEvent* e) override;

private:
    Ui::ScreenSaver* ui;
    Var::ScreenSaver var;
};
#endif // SCREENSAVER_H
