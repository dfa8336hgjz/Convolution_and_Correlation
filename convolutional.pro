QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOLUTION_DIR = $${PWD}/

SOURCES += \
    main.cpp \
    firstWin.cpp \
    process.cpp

HEADERS += \
    firstWin.h \
    process.h

FORMS += \
    firstWin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$SOLUTION_DIR/opencv/build/x64/vc15/lib/ -lopencv_world455d

INCLUDEPATH += $$SOLUTION_DIR/opencv/build/include
DEPENDPATH += $$SOLUTION_DIR/opencv/build/include

INCLUDEPATH += $$SOLUTION_DIR
