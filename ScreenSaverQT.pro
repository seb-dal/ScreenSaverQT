QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Widget/app_splashscreen.cpp \
    Widget/frameless.cpp \
    Widget/pushbuttoniconautoresize.cpp \
    Widget/qflowlayout.cpp \
    UI/screensaver.cpp \
    UI/timerbutton.cpp \
    Widget/smoothimagelabel.cpp \
    Widget/timerbutton_pushbutton.cpp \
    main.cpp \
    utils/StyleLoader.cpp\

HEADERS += \
    UI/ui_template.h \
    Widget/app_splashscreen.h \
    Widget/frameless.h \
    Widget/pushbuttoniconautoresize.h \
    Widget/qflowlayout.h \
    UI/screensaver.h \
    UI/screensaver_ui.h \
    UI/timerbutton.h \
    Widget/smoothimagelabel.h \
    Widget/timerbutton_pushbutton.h \
    UI/timerbutton_ui.h \
    model/TimerButton_DOT.h \
    utils/StyleLoader.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources/Ressources.qrc

FORMS += \
    form.ui
