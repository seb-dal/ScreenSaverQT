#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QTranslator>

class Translator {
    static QTranslator translator;

public:
    static void setLanguage();
};

#endif // TRANSLATOR_H
