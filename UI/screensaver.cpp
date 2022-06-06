#include "screensaver.h"
#include "screensaver_ui.h"

#include "utils/appConst.h"
#include "utils/processesclearer.h"

ScreenSaver::ScreenSaver(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ScreenSaver)
{
    ui->setupUi(this);
}

ScreenSaver::~ScreenSaver() { delete ui; }

void ScreenSaver::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control) {
        show_frame = !show_frame;

        ShowHideframe();
    }
    if (show_frame) {
        if (event->key() == Qt::Key_Escape) {
            this->close();
        }
    }
}

void ScreenSaver::ShowHideframe()
{
    QRect r = this->geometry();
    QSize ms = this->minimumSize();
    int wl, bw, pp;

    if (show_frame) {
        pp = -appConst::sizeFrame;
        wl = bw = appConst::sizeFrame;

    } else {
        pp = appConst::sizeFrame;
        wl = 0;
        bw = -1;
    }
    int ss = -2 * pp;

    this->setMinimumSize(ms.width() + ss, ms.height() + ss);
    this->setGeometry( //
        r.x() + pp, //
        r.y() + pp, //
        r.width() + ss, //
        r.height() + ss);

    ui->fl->setBorderWidth(bw);
    ui->frame->setMidLineWidth(wl);
}

bool ScreenSaver::event(QEvent* e)
{
    QSize frame_s(0, 0);
    QPoint frame_p(0, 0);

    switch (e->type()) {
    case QInputEvent::Show:
    case QInputEvent::WindowActivate:
        ProcessesClearer::clearAll();
        break;

    case QInputEvent::Resize:
        if (show_frame)
            frame_s = QSize(2 * appConst::sizeFrame, 2 * appConst::sizeFrame);

        Remember::put(APP::App_Size::name(), this->size() - frame_s);
        break;

    case QInputEvent::Move:
        if (show_frame)
            frame_p = QPoint(appConst::sizeFrame, appConst::sizeFrame);

        Remember::put(APP::App_Position::name(), this->pos() + frame_p);
        break;

    default:;
    }

    return QMainWindow::event(e);
}
