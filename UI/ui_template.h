#ifndef UI_TEMPLATE_H
#define UI_TEMPLATE_H

#define Ui_decl(className)                    \
    namespace Ui {                            \
    class className : public Ui_##className { \
    };                                        \
    }

#define componentCreate(var, className, parent) \
    var = new className(parent);                \
    var->setObjectName(QString::fromUtf8(#var))

#define component2Create(var, className, text, parent) \
    var = new className(text, parent);                 \
    var->setObjectName(QString::fromUtf8(#var))

#endif // UI_TEMPLATE_H
