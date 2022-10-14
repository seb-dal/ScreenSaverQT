#include "blackscreen.h"
#include <QApplication>
#include <QScreen>

#include <QLabel>

BlackScreen::BlackScreen()
    : QDialog(nullptr)
{
    QRect m;
    for (QScreen* s : QApplication::screens()) {
        m = m.united(s->geometry());
    }

    setGeometry(m);

    this->setObjectName(QString::fromUtf8("BlackScreen"));

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->setStyleSheet("background-color: rgb(0,0,0);");

    //this->showFullScreen();
}

BlackScreen::~BlackScreen()
{
}

void BlackScreen::mouseReleaseEvent(QMouseEvent* /*event*/) { this->close(); }
