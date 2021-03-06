#include "blackscreen.h"

#include <QLabel>

BlackScreen::BlackScreen(QWidget* parent)
    : QDialog(parent)
{
    this->setObjectName(QString::fromUtf8("BlackScreen"));

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->setStyleSheet("background-color: rgb(0,0,0);");

    this->showFullScreen();
}

BlackScreen::~BlackScreen()
{
}

void BlackScreen::mouseReleaseEvent(QMouseEvent* /*event*/) { this->close(); }
