# configuration of build files path

CONFIG(release, debug|release) {
    DESTDIR = release
}else{
    DESTDIR = debug
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.rcc
UI_DIR = $$DESTDIR/.ui
LRELEASE_DIR = $$DESTDIR/.lang
