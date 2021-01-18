/********************************************************************************
** Form generated from reading UI file 'media_player.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIA_PLAYER_H
#define UI_MEDIA_PLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_media_player
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *all_widgets;
    QHBoxLayout *show_in_mini;
    QPushButton *play_button;
    QPushButton *pause_button;
    QPushButton *stop_button;
    QSlider *volume_slider;
    QPushButton *button_minimize;
    QPushButton *video_button;
    QHBoxLayout *mini_no;
    QPushButton *button_previous;
    QPushButton *button_file;
    QPushButton *button_next;
    QPushButton *button_shuffle;
    QPushButton *mute_butten;
    QHBoxLayout *all_labels;
    QLabel *label;
    QTableView *playlistView;
    QHBoxLayout *progress;
    QLineEdit *lineEdit_2;
    QSlider *progress_slider;
    QLineEdit *lineEdit;

    void setupUi(QDialog *media_player)
    {
        if (media_player->objectName().isEmpty())
            media_player->setObjectName(QString::fromUtf8("media_player"));
        media_player->resize(670, 507);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(media_player->sizePolicy().hasHeightForWidth());
        media_player->setSizePolicy(sizePolicy);
        media_player->setLayoutDirection(Qt::LeftToRight);
        media_player->setAutoFillBackground(true);
        media_player->setSizeGripEnabled(false);
        media_player->setModal(false);
        layoutWidget = new QWidget(media_player);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(1, 2, 661, 381));
        all_widgets = new QVBoxLayout(layoutWidget);
        all_widgets->setSpacing(6);
        all_widgets->setContentsMargins(11, 11, 11, 11);
        all_widgets->setObjectName(QString::fromUtf8("all_widgets"));
        all_widgets->setContentsMargins(0, 0, 0, 0);
        show_in_mini = new QHBoxLayout();
        show_in_mini->setSpacing(6);
        show_in_mini->setObjectName(QString::fromUtf8("show_in_mini"));
        play_button = new QPushButton(layoutWidget);
        play_button->setObjectName(QString::fromUtf8("play_button"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(play_button->sizePolicy().hasHeightForWidth());
        play_button->setSizePolicy(sizePolicy1);

        show_in_mini->addWidget(play_button);

        pause_button = new QPushButton(layoutWidget);
        pause_button->setObjectName(QString::fromUtf8("pause_button"));
        sizePolicy1.setHeightForWidth(pause_button->sizePolicy().hasHeightForWidth());
        pause_button->setSizePolicy(sizePolicy1);

        show_in_mini->addWidget(pause_button);

        stop_button = new QPushButton(layoutWidget);
        stop_button->setObjectName(QString::fromUtf8("stop_button"));
        sizePolicy1.setHeightForWidth(stop_button->sizePolicy().hasHeightForWidth());
        stop_button->setSizePolicy(sizePolicy1);

        show_in_mini->addWidget(stop_button);

        volume_slider = new QSlider(layoutWidget);
        volume_slider->setObjectName(QString::fromUtf8("volume_slider"));
        sizePolicy1.setHeightForWidth(volume_slider->sizePolicy().hasHeightForWidth());
        volume_slider->setSizePolicy(sizePolicy1);
        volume_slider->setValue(50);
        volume_slider->setOrientation(Qt::Horizontal);

        show_in_mini->addWidget(volume_slider);

        button_minimize = new QPushButton(layoutWidget);
        button_minimize->setObjectName(QString::fromUtf8("button_minimize"));
        sizePolicy1.setHeightForWidth(button_minimize->sizePolicy().hasHeightForWidth());
        button_minimize->setSizePolicy(sizePolicy1);
        button_minimize->setMinimumSize(QSize(93, 28));

        show_in_mini->addWidget(button_minimize);

        video_button = new QPushButton(layoutWidget);
        video_button->setObjectName(QString::fromUtf8("video_button"));
        sizePolicy1.setHeightForWidth(video_button->sizePolicy().hasHeightForWidth());
        video_button->setSizePolicy(sizePolicy1);

        show_in_mini->addWidget(video_button);


        all_widgets->addLayout(show_in_mini);

        mini_no = new QHBoxLayout();
        mini_no->setSpacing(6);
        mini_no->setObjectName(QString::fromUtf8("mini_no"));
        button_previous = new QPushButton(layoutWidget);
        button_previous->setObjectName(QString::fromUtf8("button_previous"));

        mini_no->addWidget(button_previous);

        button_file = new QPushButton(layoutWidget);
        button_file->setObjectName(QString::fromUtf8("button_file"));

        mini_no->addWidget(button_file);

        button_next = new QPushButton(layoutWidget);
        button_next->setObjectName(QString::fromUtf8("button_next"));

        mini_no->addWidget(button_next);

        button_shuffle = new QPushButton(layoutWidget);
        button_shuffle->setObjectName(QString::fromUtf8("button_shuffle"));

        mini_no->addWidget(button_shuffle);

        mute_butten = new QPushButton(layoutWidget);
        mute_butten->setObjectName(QString::fromUtf8("mute_butten"));

        mini_no->addWidget(mute_butten);


        all_widgets->addLayout(mini_no);

        all_labels = new QHBoxLayout();
        all_labels->setSpacing(6);
        all_labels->setObjectName(QString::fromUtf8("all_labels"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        all_labels->addWidget(label);

        playlistView = new QTableView(layoutWidget);
        playlistView->setObjectName(QString::fromUtf8("playlistView"));

        all_labels->addWidget(playlistView);


        all_widgets->addLayout(all_labels);

        progress = new QHBoxLayout();
        progress->setSpacing(2);
        progress->setObjectName(QString::fromUtf8("progress"));
        progress->setSizeConstraint(QLayout::SetMinimumSize);
        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy3);

        progress->addWidget(lineEdit_2);

        progress_slider = new QSlider(layoutWidget);
        progress_slider->setObjectName(QString::fromUtf8("progress_slider"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(progress_slider->sizePolicy().hasHeightForWidth());
        progress_slider->setSizePolicy(sizePolicy4);
        progress_slider->setOrientation(Qt::Horizontal);

        progress->addWidget(progress_slider);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy3.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy3);

        progress->addWidget(lineEdit);


        all_widgets->addLayout(progress);


        retranslateUi(media_player);

        QMetaObject::connectSlotsByName(media_player);
    } // setupUi

    void retranslateUi(QDialog *media_player)
    {
        media_player->setWindowTitle(QApplication::translate("media_player", "media_player", nullptr));
        play_button->setText(QString());
        pause_button->setText(QString());
        stop_button->setText(QString());
        button_minimize->setText(QString());
        video_button->setText(QString());
        button_previous->setText(QString());
        button_file->setText(QString());
        button_next->setText(QString());
        button_shuffle->setText(QApplication::translate("media_player", "Shuffle", nullptr));
        mute_butten->setText(QString());
        label->setText(QApplication::translate("media_player", "Album art", nullptr));
        lineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class media_player: public Ui_media_player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIA_PLAYER_H
