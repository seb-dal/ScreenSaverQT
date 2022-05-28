#include "screensaver.h"
#include "screensaver_ui.h"

#include "utils/processesclearer.h"

ScreenSaver::ScreenSaver(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ScreenSaver)
{
    ui->setupUi(this);
}

ScreenSaver::~ScreenSaver()
{
    delete ui;
}

void ScreenSaver::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control) {
        var.show_frame = !var.show_frame;

        ShowHideframe();
    }
    if (var.show_frame) {
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

    if (var.show_frame) {
        pp = -8;
        wl = bw = 8;

    } else {
        pp = 8;
        wl = 0;
        bw = -1;
    }
    int ss = (-2) * pp;

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
    switch (e->type()) {
    case QInputEvent::Show:
        ProcessesClearer::clearAll();
        break;

    case QInputEvent::Resize:
        Remember::put(APP::App_Size::name(), this->size());
        break;
    case QInputEvent::Move:
        Remember::put(APP::App_Position::name(), this->pos());
        break;
    default:
        break;
    }

    return QMainWindow::event(e);
}
