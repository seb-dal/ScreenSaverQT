#include "StyleLoader.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

void StyleLoader::loadStyle(QWidget* elem, const QString& styleFile)
{
    QFile file(styleFile);
    QString style;
    if (!file.open(QFile::OpenModeFlag::ReadOnly)) {
        qCritical() << "Fail to open stylesheet file :" << styleFile;
    }

    QTextStream in(&file);
    while (!in.atEnd())
        style += in.readLine();

    elem->setStyleSheet(style);
}
