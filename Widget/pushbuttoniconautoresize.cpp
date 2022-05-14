#include "pushbuttoniconautoresize.h"

#include <QSize>
#include <QSizePolicy>
#include <QStyleOptionButton>
#include <QStylePainter>
#include <QtGlobal>

PushButtonIconAutoResize::PushButtonIconAutoResize(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{
    pad = 4;
    minSize = 8;

    this->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
}

PushButtonIconAutoResize::~PushButtonIconAutoResize() { }

void PushButtonIconAutoResize::paintEvent(QPaintEvent* /*event*/)
{
    QStylePainter painter(this);
    painter.setRenderHints(
        QStylePainter::RenderHint::Antialiasing
        | QStylePainter::RenderHint::LosslessImageRendering
        | QStylePainter::RenderHint::SmoothPixmapTransform);

    QStyleOptionButton opt;
    this->initStyleOption(&opt);

    QRect r = opt.rect;

    int h = this->size().height(); //r.height();
    int w = this->size().width(); //r.width();
    int iconSize = qMax(qMin(h, w) - 2 * this->pad, this->minSize);

    QSize newSize = QSize(iconSize, iconSize);
    opt.iconSize = newSize;
    this->setIconSize(newSize);
    painter.drawControl(QStyle::CE_PushButton, opt);
}
