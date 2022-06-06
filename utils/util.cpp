#include "util.h"

#include "UI/ui_template.h"
#include "utils/appConst.h"
#include <QFont>

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
