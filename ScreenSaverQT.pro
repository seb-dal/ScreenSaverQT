QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

CONFIG(release, debug|release) {
    message( "release" )
    QMAKE_CXXFLAGS_RELEASE += -Ofast
    TARGET = ScreenSaver
}

CONFIG += lrelease
CONFIG += embed_translations

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UI/blackscreen.cpp \
    UI/dialbutton.cpp \
    UI/semitransparentscreen.cpp \
    Widget/app_splashscreen.cpp \
    Widget/frameless.cpp \
    UI/screensaver.cpp \
    UI/timerbutton.cpp \
    Widget/smoothimagelabel.cpp \
    Widget/timerbutton_pushbutton.cpp \
    main.cpp \
    utils/StyleLoader.cpp\
    utils/processesclearer.cpp \
    utils/remember.cpp \
    utils/translator.cpp \
    utils/util.cpp

HEADERS += \
    UI/blackscreen.h \
    UI/dialbutton.h \
    UI/dialbutton_ui.h \
    UI/semitransparentscreen.h \
    UI/ui_template.h \
    Widget/app_splashscreen.h \
    Widget/frameless.h \
    UI/screensaver.h \
    UI/screensaver_ui.h \
    UI/timerbutton.h \
    Widget/smoothimagelabel.h \
    Widget/timerbutton_pushbutton.h \
    UI/timerbutton_ui.h \
    lib/include/fameta-counter \
    model/TimerButton_DOT.h \
    utils/Remember_keys.h \
    utils/StyleLoader.h \
    utils/appConst.h \
    utils/processesclearer.h \
    utils/remember.h \
    utils/translator.h \
    utils/util.h \
    utils/utilMacro.h

RC_ICONS = ./ressources/img/icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources/Ressources.qrc

TRANSLATIONS += \
    ressources/lang/ScreenSaver_en.ts \
    ressources/lang/ScreenSaver_fr.ts


include(ConfigBuildFiles.pri)

include(ConfigDeployementAPP.pri)

FORMS +=
