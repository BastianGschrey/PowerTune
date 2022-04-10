unix:!android {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/PowerTune/
        }
        export(target.path)
    }
    INSTALLS += target
}

export(INSTALLS)

