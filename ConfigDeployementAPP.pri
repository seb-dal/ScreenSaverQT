# Deployement APP

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
    DEPLOY_COMMAND = $$QT_INSTALL_BINS/windeployqt$${TARGET_CUSTOM_EXT}
}
macx {
    DEPLOY_COMMAND = $$QT_INSTALL_BINS/macdeployqt$${TARGET_CUSTOM_EXT}
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
