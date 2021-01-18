#include "customization.h"

QString customization::getWindowStyleSheet()
{
    return "QWidget { "
           "background-color: #454545; "
           "border: 1px solid black; "
           "}";
}

QString customization::getLabelStyleSheet()
{
    return "QLabel { "
           "color: #8f8f8f; "
           "border: none; "
           "margin: 6px; "
           "}";
}

QString customization::getNextStyleSheet()
{
    return "QPushButton { "
           "image: url(:/new/icons/buttons/skip-next.png);"
           "background-color: #292929;"
           "icon-size: 24px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QPushButton:hover {"
           "image: url(:/new/icons/buttons/skip-next-orange.png);}"
           "}";
}

QString customization::getPreviousStyleSheet()
{
    return "QPushButton { "
           "image: url(:/new/icons/buttons/skip-previous.png);"
           "background-color: #292929;"
           "icon-size: 24px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QPushButton:hover {"
           "image: url(:/new/icons/buttons/skip-previous-orange.png);}"
           "}";
}

QString customization::getStopStyleSheet()
{
    return "QPushButton { "
           "image: url(:/new/icons/buttons/stop.png);"
           "background-color: #292929;"
           "icon-size: 24px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QPushButton:hover {"
           "image: url(:/new/icons/buttons/stop-orange.png);}"
           "}";
}

QString customization::getPlayStyleSheet()
{
    return "QPushButton { "
           "image: url(:/new/icons/buttons/play.png);"
           "background-color: #292929;"
           "icon-size: 48px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QPushButton:hover {"
           "image: url(:/new/icons/buttons/play-orange.png);}"
           "}";
}///

QString customization::getPauseStyleSheet()
{
    return "QPushButton { "
           "image: url(:/new/icons/buttons/pause.png);"
           "background-color: #292929;"
           "icon-size: 24px;"
           "padding: 6px;"
           "margin: 6px;"
           "border: none;"
           "}"
           "QPushButton:hover {"
           "image: url(:/new/icons/buttons/pause-orange.png);}"
           "}";
}

QString customization::getMenuStyleSheet()
{
    return "QPushButton { "
           "image: url(:/new/icons/buttons/window-restore-gray.png);"
           "color: #8f8f8f;"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QPushButton:hover {"
           "image: url(:/new/icons/buttons/window-restore.png);}"
           "}";
}

QString customization::getShuffleStyleSheet()
{
    return "QPushButton { "
           "color: #8f8f8f;"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QPushButton:hover {"
           "color: #f09900;}"
           "}";
}

QString customization::getMinimizationStyleSheet()
{
    return "QPushButton { "
           "image: url(:/new/icons/buttons/window-minimize-gray.png);"
           "color: #8f8f8f;"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QPushButton:hover {"
           "image: url(:/new/icons/buttons/window-minimize.png);}"
           "}";
}

QString customization::getMaximizationStyleSheet()
{
    return "QPushButton { "
           "image: url(:/new/icons/buttons/window-maximize-gray.png);"
           "color: #8f8f8f;"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QPushButton:hover {"
           "image: url(:/new/icons/buttons/window-maximize.png);}"
           "}";
}

QString customization::getMuteStyleSheet()
{
    return "QPushButton { "
           "color: #8f8f8f;"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QPushButton:hover {"
           "color: #f09900;}"
           "}";
}


QString customization::getTableViewStyleSheet()
{
    return "QTableView { "
           "background-color: gray; "
           "color: black; "
           "border: 1px solid #e2e2de;"
           "}"
           "QTableView::item:selected {"
           "background-color: #de8e37;"
           "}"
           "QHeaderView::section:horizintal {"
           "background-color: white;"
           "border-style: none;"
           "color: black; "
           "border: 1px solid #e2e2de; "
           "padding: 6px; "
           "}";
}

QString customization::getVideoStyleSheet()
{
    return "QPushButton { "
           "color: #8f8f8f;"
           "background-color: #292929;"
           "icon-size: 12px;"
           "padding-left: 10px;"
           "padding-right: 10px;"
           "padding-top: 5px;"
           "padding-bottom: 5px;"
           "border: 1px solid #292929; "
           "}"
           "QPushButton:hover {"
           "color: #f09900;}"
           "}";
}

QString customization::getSliderStyleSheet()
{
    return "QSlider::handle::horizontal{"
           "background: #ffffff"
           "}"
           "QSlider::handle::horizontal:pressed{"
           "background: #f09900"
           "}"
           "QSlider::handle::horizontal::hover{"
           "background: #f09900"
           "}";
}

