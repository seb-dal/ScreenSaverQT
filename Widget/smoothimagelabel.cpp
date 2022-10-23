#include "smoothimagelabel.h"

#include <QStyleOptionButton>
#include <QStylePainter>

SmoothImageLabel::SmoothImageLabel(QWidget* parent)
    : QLabel(parent)
{
}

SmoothImageLabel::~SmoothImageLabel()
{
}

void SmoothImageLabel::setCurrent(QImage* pix)
{
    current = pix;
    repaint();
}

void SmoothImageLabel::paintEvent(QPaintEvent*)
{
    QStylePainter painter(this);
    painter.setRenderHints( //
        QStylePainter::RenderHint::Antialiasing //
        | QStylePainter::RenderHint::LosslessImageRendering //
        | QStylePainter::RenderHint::SmoothPixmapTransform);

    QRect rec = rect();
    QPoint p = rec.center();

    int min = qMin(rec.height(), rec.width());
    rec.setHeight(min);
    rec.setWidth(min);
    rec.moveCenter(p);

    painter.drawImage(rec, *current);
}
