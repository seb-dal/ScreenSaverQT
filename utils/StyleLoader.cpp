#include "StyleLoader.h"
#include "qdebug.h"

#include <QFile>
#include <QTextStream>

void StyleLoader::loadStyle(QWidget* elem, const QString& styleFile)
{
    QFile file(styleFile);
    QString style;
    if (file.open(QFile::OpenModeFlag::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd())
            style += in.readLine();
    } else {
        qCritical() << "Fail to open stylesheet file :" << styleFile;
    }
    elem->setStyleSheet(style);
}
