#ifndef STYLELOADER_H
#define STYLELOADER_H

#include <QWidget>
#include <QString>

class StyleLoader{
public:
    static void loadStyle(QWidget* elem, const QString& styleFile);
};

#endif // STYLELOADER_H
