#include "translator.h"

#include "utils/Remember_keys.h"
#include "utils/remember.h"
#include <QApplication>
#include <QLocale>

QTranslator Translator::translator;

void Translator::setLanguage()
{
    QString file = "ScreenSaver_" + Remember::get_(APP::Language::name(), QString("en")).toLower();

    if (translator.load(":/i18n/" + file + ".qm"))
        QCoreApplication::installTranslator(&translator);
}
