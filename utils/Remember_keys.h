#ifndef REMEMBER_KEYS_H
#define REMEMBER_KEYS_H

#include "lib/include/fameta-counter"
#include <QList>
#include <QString>

#define EnumClass(NAME, BASE, COUNT)                        \
    class NAME : public BASE {                              \
        static constexpr int i = COUNT.next<__COUNTER__>(); \
                                                            \
    public:                                                 \
        static int id() { return i; }                       \
        static const QString name() { return #NAME; }       \
    }

//
constexpr fameta::counter<__COUNTER__, 0> C2;
class APP {
    class EnumClass_Base {
    public:
        static int nb_child() { return C2.current<__COUNTER__>(); }
    };

public:
    EnumClass(App_Size, EnumClass_Base, C2);
    EnumClass(App_Position, EnumClass_Base, C2);

    EnumClass(Number_After_Dot, EnumClass_Base, C2);
    EnumClass(Time_After_Button_Clicked, EnumClass_Base, C2);
    EnumClass(Hide_After_Action, EnumClass_Base, C2);
    EnumClass(Standby_HibernateMode, EnumClass_Base, C2);

    EnumClass(Show_Standby_Button, EnumClass_Base, C2);
    EnumClass(Show_ScreenOff_Button, EnumClass_Base, C2);
    EnumClass(Show_BlackScreen_Button, EnumClass_Base, C2);
    EnumClass(Show_ShadeScreen_Button, EnumClass_Base, C2);
};

#endif // REMEMBER_KEYS_H
