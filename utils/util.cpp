#include "util.h"

#include <QApplication>
#include <QFont>
#include <QScreen>

#include "UI/ui_template.h"
#include "utils/appConst.h"

void util::setFontSize(QWidget* obj, int size)
{
    QFont f = obj->font();
    f.setPixelSize(size);
    obj->setFont(f);
}

void util::setFontBold(QWidget* obj, bool bold)
{
    QFont f = obj->font();
    f.setBold(bold);
    obj->setFont(f);
}

void util::setSizePolicy(QWidget* obj, QSizePolicy::Policy horizontal, QSizePolicy::Policy vertical)
{
    QSizePolicy sizePolicy(horizontal, vertical);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(obj->hasHeightForWidth());

    obj->setSizePolicy(sizePolicy);
}

int util::powTenInt(int nb)
{
    int x = 1;
    for (int i = 0; i < nb; ++i)
        x *= 10;
    return x;
}

float util::computeRatio(QWidget* obj, int* sizeSquare)
{
    QSize s = obj->size();
    int size = qMin(s.height(), s.width());

    if (sizeSquare != nullptr)
        (*sizeSquare) = size;

    return size / appConst::sizeDivRatio;
}

void util::setMultiScreenGeom(QWidget* obj)
{
    QRect m;
    for (QScreen* s : QApplication::screens()) {
        m = m.united(s->geometry());
    }
    obj->setGeometry(m);
}
