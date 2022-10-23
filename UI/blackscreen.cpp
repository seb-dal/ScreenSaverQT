#include "blackscreen.h"

#include <QLabel>

#include "utils/util.h"

BlackScreen::BlackScreen()
    : QDialog(nullptr)
{
    util::setMultiScreenGeom(this);

    this->setObjectName(QString::fromUtf8("BlackScreen"));

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->setStyleSheet("background-color: rgb(0,0,0);");

    //this->showFullScreen();
}

BlackScreen::~BlackScreen()
{
}

void BlackScreen::mouseReleaseEvent(QMouseEvent* /*event*/) { this->close(); }
