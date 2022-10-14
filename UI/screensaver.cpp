#include "screensaver.h"
#include "screensaver_ui.h"

#include "options.h"
#include <QMenu>

#include "utils/Remember_keys.h"
#include "utils/appConst.h"
#include "utils/processesclearer.h"
#include "utils/utilMacro.h"

bool ScreenSaver::reboot = false;
;

ScreenSaver::ScreenSaver(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ScreenSaver)
{
    ui->setupUi(this);

    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));
}

ScreenSaver::~ScreenSaver() { deleteIfReq(ui); }

void ScreenSaver::rebootApp()
{
    ScreenSaver::reboot = true;
    this->close();
}

void ScreenSaver::ShowContextMenu(const QPoint& pos)
{
    QVariant show_context_menu = Remember::get_<int>(APP::ShowContextMenu::name(), 1);
    if (!show_context_menu.toBool()) {
        return;
    }

    QMenu contextMenu(this);

    contextMenu.setStyleSheet("");
    {
        contextMenu.addAction(show_frame ? tr("Hide Frame") : tr("Show Frame"), [this] {
            show_frame = !show_frame;
            ShowHideframe();
        });
        contextMenu.addSeparator();

        contextMenu.addAction(tr("Options"), [this] {
            Options opt(this);
            opt.show();
            opt.exec();
            if (opt.result() == QDialog::Accepted) {
                rebootApp();
            }
        });
        contextMenu.addSeparator();

        contextMenu.addAction(tr("Quit"), [this] { close(); });
    }
    contextMenu.exec(mapToGlobal(pos));
}

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

    if (!show_frame) {
        rebootApp();
    }
}

bool ScreenSaver::event(QEvent* e)
{
    QSize frame_s(0, 0);
    QPoint frame_p(0, 0);

    switch (e->type()) {
    case QInputEvent::Show:
    case QInputEvent::WindowActivate:
        ProcessesClearer::clearAll();
        return true;
        break;

    case QInputEvent::Resize:
        if (show_frame)
            frame_s = QSize(2 * appConst::sizeFrame, 2 * appConst::sizeFrame);

        Remember::put(APP::App_Size::name(), this->size() - frame_s);
        return true;
        break;

    case QInputEvent::Move:
        if (show_frame)
            frame_p = QPoint(appConst::sizeFrame, appConst::sizeFrame);

        Remember::put(APP::App_Position::name(), this->pos() + frame_p);
        return true;
        break;

    default:;
    }

    return QMainWindow::event(e);
}
