#include "remember.h"

#include <QStandardPaths>

QSettings* Remember::iniFile = nullptr;

void Remember::initialize()
{
    QString path = "./conf.ini";
    iniFile = new QSettings(path, QSettings::IniFormat);
}

void Remember::saveData()
{
    iniFile->sync();
}

void Remember::put(const QString name, const QVariant& val)
{
    iniFile->setValue(name, val);
}

QVariant Remember::get(const QString name)
{
    return iniFile->value(name);
}
