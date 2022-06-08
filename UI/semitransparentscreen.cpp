#include "semitransparentscreen.h"

#include "utils/utilMacro.h"
#include <QApplication>
#include <QScreen>

SemiTransparentScreen::SemiTransparentScreen(QWidget* parent)
    : QWidget(parent)
{
    frame = new QLabel(this);

    frame->setAttribute(Qt::WA_ShowWithoutActivating);

    QRect m;
    for (QScreen* s : QApplication::screens()) {
        m = m.united(s->geometry());
    }

    setGeometry(m);
    //showFullScreen();
    frame->setGeometry(geometry());
    frame->setAlignment(Qt::AlignmentFlag::AlignCenter);
    frame->setText(" ");

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags( //
        Qt::WindowStaysOnTopHint //
        | Qt::SplashScreen //
        | Qt::FramelessWindowHint //
        | Qt::WindowTransparentForInput //
        | Qt::WindowStaysOnTopHint //
        | Qt::Tool);

    frame->setStyleSheet("background-color: #00000000;");

    setAttribute(Qt::WA_TransparentForMouseEvents);
    frame->setAttribute(Qt::WA_TransparentForMouseEvents);
    //showFullScreen();
}

SemiTransparentScreen::~SemiTransparentScreen()
{
    deleteIfReq(frame);
}

void SemiTransparentScreen::setTransparenty(int tr)
{
    // bug stylesheet : rgba(0,0,0,1) == rgba(0,0,0,255)
    frame->setStyleSheet(
        QString("background-color: %1;")
            .arg(QColor(0, 0, 0, tr).name(QColor::HexArgb)));
}
