#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QFrame>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class ScreenSaver;
}
QT_END_NAMESPACE

class ScreenSaver : public QFrame {
    Q_OBJECT

public:
    ScreenSaver(QWidget* parent = nullptr);
    ~ScreenSaver();

private:
    Ui::ScreenSaver* ui;
};
#endif // SCREENSAVER_H
