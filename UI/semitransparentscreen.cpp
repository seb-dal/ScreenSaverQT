#include "semitransparentscreen.h"

#include "utils/util.h"
#include "utils/utilMacro.h"

int SemiTransparentScreen::transparency_save = 0;

SemiTransparentScreen::SemiTransparentScreen()
    : QWidget(/*parent*/) // removed parent-children link so that "ICONIFY" doesn't iconify this screen
{
    frame = new QLabel(this);

    frame->setAttribute(Qt::WA_ShowWithoutActivating);

    util::setMultiScreenGeom(this);

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
    transparency_save = tr;
    frame->setStyleSheet(
        QString("background-color: %1;")
            .arg(QColor(0, 0, 0, tr).name(QColor::HexArgb)));
}

int SemiTransparentScreen::getTransparency_save()
{
    return transparency_save;
}
