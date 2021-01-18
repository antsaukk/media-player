/********************************************************************************
** Form generated from reading UI file 'video_player.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO_PLAYER_H
#define UI_VIDEO_PLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_video_player
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *previous_button;
    QPushButton *play_button;
    QPushButton *pause_button;
    QPushButton *stop_button;
    QPushButton *next_button;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *position;
    QSlider *progress_slider;
    QLineEdit *duration;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *video;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_1;
    QSlider *volume_slider;
    QPushButton *mute_button;
    QPushButton *add_button;

    void setupUi(QWidget *video_player)
    {
        if (video_player->objectName().isEmpty())
            video_player->setObjectName(QString::fromUtf8("video_player"));
        video_player->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(video_player->sizePolicy().hasHeightForWidth());
        video_player->setSizePolicy(sizePolicy);
        horizontalLayoutWidget = new QWidget(video_player);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 550, 801, 25));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        previous_button = new QPushButton(horizontalLayoutWidget);
        previous_button->setObjectName(QString::fromUtf8("previous_button"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(previous_button->sizePolicy().hasHeightForWidth());
        previous_button->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(previous_button);

        play_button = new QPushButton(horizontalLayoutWidget);
        play_button->setObjectName(QString::fromUtf8("play_button"));
        sizePolicy1.setHeightForWidth(play_button->sizePolicy().hasHeightForWidth());
        play_button->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(play_button);

        pause_button = new QPushButton(horizontalLayoutWidget);
        pause_button->setObjectName(QString::fromUtf8("pause_button"));
        sizePolicy1.setHeightForWidth(pause_button->sizePolicy().hasHeightForWidth());
        pause_button->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(pause_button);

        stop_button = new QPushButton(horizontalLayoutWidget);
        stop_button->setObjectName(QString::fromUtf8("stop_button"));
        sizePolicy1.setHeightForWidth(stop_button->sizePolicy().hasHeightForWidth());
        stop_button->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(stop_button);

        next_button = new QPushButton(horizontalLayoutWidget);
        next_button->setObjectName(QString::fromUtf8("next_button"));
        sizePolicy1.setHeightForWidth(next_button->sizePolicy().hasHeightForWidth());
        next_button->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(next_button);

        horizontalLayoutWidget_2 = new QWidget(video_player);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 570, 801, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        position = new QLineEdit(horizontalLayoutWidget_2);
        position->setObjectName(QString::fromUtf8("position"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(position->sizePolicy().hasHeightForWidth());
        position->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(position);

        progress_slider = new QSlider(horizontalLayoutWidget_2);
        progress_slider->setObjectName(QString::fromUtf8("progress_slider"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(progress_slider->sizePolicy().hasHeightForWidth());
        progress_slider->setSizePolicy(sizePolicy3);
        progress_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(progress_slider);

        duration = new QLineEdit(horizontalLayoutWidget_2);
        duration->setObjectName(QString::fromUtf8("duration"));
        sizePolicy2.setHeightForWidth(duration->sizePolicy().hasHeightForWidth());
        duration->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(duration);

        verticalLayoutWidget = new QWidget(video_player);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 801, 521));
        video = new QVBoxLayout(verticalLayoutWidget);
        video->setObjectName(QString::fromUtf8("video"));
        video->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_3 = new QWidget(video_player);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 520, 801, 25));
        horizontalLayout_1 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        horizontalLayout_1->setContentsMargins(0, 0, 0, 0);
        volume_slider = new QSlider(horizontalLayoutWidget_3);
        volume_slider->setObjectName(QString::fromUtf8("volume_slider"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(volume_slider->sizePolicy().hasHeightForWidth());
        volume_slider->setSizePolicy(sizePolicy4);
        volume_slider->setMaximumSize(QSize(75, 22));
        volume_slider->setValue(50);
        volume_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_1->addWidget(volume_slider);

        mute_button = new QPushButton(horizontalLayoutWidget_3);
        mute_button->setObjectName(QString::fromUtf8("mute_button"));
        sizePolicy1.setHeightForWidth(mute_button->sizePolicy().hasHeightForWidth());
        mute_button->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(mute_button);

        add_button = new QPushButton(horizontalLayoutWidget_3);
        add_button->setObjectName(QString::fromUtf8("add_button"));
        sizePolicy1.setHeightForWidth(add_button->sizePolicy().hasHeightForWidth());
        add_button->setSizePolicy(sizePolicy1);

        horizontalLayout_1->addWidget(add_button);


        retranslateUi(video_player);

        QMetaObject::connectSlotsByName(video_player);
    } // setupUi

    void retranslateUi(QWidget *video_player)
    {
        video_player->setWindowTitle(QApplication::translate("video_player", "Video player", nullptr));
#ifndef QT_NO_TOOLTIP
        previous_button->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        previous_button->setText(QApplication::translate("video_player", "Previous", nullptr));
#ifndef QT_NO_TOOLTIP
        play_button->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        play_button->setText(QApplication::translate("video_player", "Play", nullptr));
#ifndef QT_NO_TOOLTIP
        pause_button->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pause_button->setText(QApplication::translate("video_player", "Pause", nullptr));
        stop_button->setText(QApplication::translate("video_player", "Stop", nullptr));
        next_button->setText(QApplication::translate("video_player", "Next", nullptr));
        mute_button->setText(QApplication::translate("video_player", "Mute", nullptr));
        add_button->setText(QApplication::translate("video_player", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class video_player: public Ui_video_player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO_PLAYER_H
