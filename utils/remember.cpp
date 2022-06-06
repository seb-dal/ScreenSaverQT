#include "remember.h"

#include <QSettings>
#include <QStandardPaths>

QHash<QString, QVariant> Remember::values;

void Remember::initialize()
{
    QString path = "./conf.ini";
    QSettings* iniFile = new QSettings(path, QSettings::IniFormat);

    for (const QString& key : iniFile->allKeys()) {
        values.insert(key, iniFile->value(key));
    }

    delete iniFile;
}

void Remember::saveData()
{
    QString path = "./conf.ini";
    QSettings* iniFile = new QSettings(path, QSettings::IniFormat);

    for (auto key = values.keyBegin(); key != values.keyEnd(); ++key) {
        iniFile->setValue(*key, values.value(*key));
    }

    iniFile->sync();
    delete iniFile;
}

void Remember::put(const QString name, const QVariant& val) { values.insert(name, val); }

QVariant Remember::get(const QString name) { return values.value(name); }
