#ifndef UTIL_H
#define UTIL_H

#include <QWidget>

class util {
public:
    static void setFontSize(QWidget* obj, int size);

    static void setFontBold(QWidget* obj, bool bold);

    static void setSizePolicy(QWidget* obj,
        QSizePolicy::Policy horizontal,
        QSizePolicy::Policy vertical);

    static int powTenInt(int nb);

    static float computeRatio(QWidget* obj, int* sizeSquare = nullptr);

    static void setMultiScreenGeom(QWidget* obj);
};

#endif // UTIL_H
