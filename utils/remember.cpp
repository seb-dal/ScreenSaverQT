#include "remember.h"

#include <QStandardPaths>

QSettings* Remember::iniFile = nullptr;
QHash<QString, QVariant> Remember::values;

void Remember::initialize()
{
    QString path = "./conf.ini";
    iniFile = new QSettings(path, QSettings::IniFormat);

    for (const QString& key : iniFile->allKeys()) {
        values.insert(key, iniFile->value(key));
    }
}

void Remember::saveData()
{
    for (auto key = values.keyBegin(); key != values.keyEnd(); ++key) {
        iniFile->setValue(*key, values.value(*key));
    }
    iniFile->sync();
}

void Remember::put(const QString name, const QVariant& val)
{
    values.insert(name, val);
}

QVariant Remember::get(const QString name)
{
    return values.value(name);
}
