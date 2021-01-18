#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T18:12:21
#
#-------------------------------------------------

QT       += \
            core gui \
            core gui multimedia \
            multimedia \
            widgets \
            network \
            multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = media_player_82
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    playlist.cpp \
    id3_frame.cpp \
    id3_tag.cpp \
    media_player.cpp \
    song.cpp \
    customization.cpp \
    video_player.cpp \
    tester.cpp
    video_player.cpp

HEADERS += \
    playlist.h \
    id3_frame.h \
    id3_tag.h \
    media_player.h \
    song.h \
    customization.h \
    video_player.h \
    tester.h
    video_player.h

FORMS += \
        media_player.ui \
        video_player.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    media_player_82.pro.user \
    media_player_82.pro.user.8cee0c2 \
    media_player_82.pro.user.323cc4a

SUBDIRS += \
    media_player_82.pro

RESOURCES += \
    res.qrc
