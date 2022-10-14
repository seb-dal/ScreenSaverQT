#include "translator.h"

#include "utils/Remember_keys.h"
#include "utils/remember.h"
#include <QApplication>
#include <QLocale>

QTranslator Translator::translator;

void Translator::setLanguage(QString lang)
{
    free();
    QString file = "ScreenSaver_" + lang.toLower();

    if (translator.load(":/i18n/" + file + ".qm"))
        QCoreApplication::installTranslator(&translator);
}

void Translator::free()
{
    if (!translator.isEmpty())
        QCoreApplication::removeTranslator(&translator);
}
