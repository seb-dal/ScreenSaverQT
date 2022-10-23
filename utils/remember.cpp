#include "remember.h"

#include "utils/utilMacro.h"
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

    deleteIfReq(iniFile);
}

void Remember::saveData()
{
    QString path = "./conf.ini";
    QSettings* iniFile = new QSettings(path, QSettings::IniFormat);

    auto keys = values.keys();
    keys.sort();
    for (auto key = keys.begin(); key != keys.end(); ++key) {
        iniFile->setValue(*key, values.value(*key));
    }

    iniFile->sync();
    deleteIfReq(iniFile);
}

void Remember::put(const QString name, const QVariant& val) { values.insert(name, val); }

QVariant Remember::get(const QString name) { return values.value(name); }
