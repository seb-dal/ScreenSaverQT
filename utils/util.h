#ifndef UTIL_H
#define UTIL_H

#include <QWidget>

class util {
public:
    static void setFontSize(QWidget* obj, int size);

    static void setFontBold(QWidget* obj, bool bold);

    static int powTenInt(int nb);

    static float computeRatio(QWidget* obj, int* sizeSquare = nullptr);
};

#endif // UTIL_H
