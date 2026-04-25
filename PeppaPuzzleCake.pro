QT       += core gui widgets multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AnswerDialog.cpp \
    CakeScene.cpp \
    CardPuzzleDialog.cpp \
    FlipGameDialog.cpp \
    GameScene.cpp \
    GraphicsImageButton.cpp \
    ItemManager.cpp \
    LightPuzzle.cpp \
    PeppaDialog.cpp \
    PuzzleDialog.cpp \
    TipDialog.cpp \
    main.cpp \
    MainScene.cpp

HEADERS += \
    AnswerDialog.h \
    CakeScene.h \
    CardPuzzleDialog.h \
    FlipGameDialog.h \
    GameScene.h \
    GraphicsImageButton.h \
    ItemManager.h \
    LightPuzzle.h \
    MainScene.h \
    PeppaDialog.h \
    PuzzleDialog.h \
    TipDialog.h

FORMS += \
    MainScene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
