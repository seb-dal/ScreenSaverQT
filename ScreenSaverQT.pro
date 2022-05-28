QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UI/blackscreen.cpp \
    UI/dialbutton.cpp \
    UI/semitransparentscreen.cpp \
    Widget/app_splashscreen.cpp \
    Widget/frameless.cpp \
    Widget/qflowlayout.cpp \
    UI/screensaver.cpp \
    UI/timerbutton.cpp \
    Widget/smoothimagelabel.cpp \
    Widget/timerbutton_pushbutton.cpp \
    main.cpp \
    utils/StyleLoader.cpp\
    utils/processesclearer.cpp \
    utils/remember.cpp

HEADERS += \
    UI/blackscreen.h \
    UI/dialbutton.h \
    UI/dialbutton_ui.h \
    UI/semitransparentscreen.h \
    UI/ui_template.h \
    Widget/app_splashscreen.h \
    Widget/frameless.h \
    Widget/qflowlayout.h \
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
    utils/processesclearer.h \
    utils/remember.h

RC_ICONS = ./ressources/img/icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources/Ressources.qrc



Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui



CONFIG(release, debug|release) {
    message( "release" )
    QMAKE_CXXFLAGS_RELEASE  += -Ofast
    TARGET=ScreenSaver
}


isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    DEPLOY_COMMAND = windeployqt
}
macx {
    DEPLOY_COMMAND = macdeployqt
}

CONFIG( debug, debug|release ) {
    # debug
    #DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))

    # Use += instead of = if you use multiple QMAKE_POST_LINKs
    QMAKE_POST_LINK += $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
}

#  # Uncomment the following line to help debug the deploy command when running qmake
#  warning($${DEPLOY_COMMAND} $${DEPLOY_TARGET})

