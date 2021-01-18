#include "video_player.h"
#include "ui_video_player.h"
#include "customization.h"

/*
* AALTO C++ media_player_8
* @function_type: Constructor
* @desc: Constructs the object
* @param: parent
* @return: The constructed object
*/
video_player::video_player(QWidget *parent) : QWidget(parent), ui(new Ui::video_player)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
    ui->video->addWidget(videoWidget);
    connect(player, &QMediaPlayer::positionChanged, this, &video_player::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &video_player::on_durationChanged);
    connect(player, &QMediaPlayer::positionChanged, ui->progress_slider, &QSlider::setValue);
    connect(player, &QMediaPlayer::durationChanged, ui->progress_slider, &QSlider::setMaximum);
    connect(ui->progress_slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);
    connect(ui->volume_slider, &QSlider::sliderMoved, player, &QMediaPlayer::setVolume);
    setAcceptDrops(true);

    setWindowFlags(Qt::WindowTitleHint);

    palet = new QPalette();
    palet->setColor(QPalette::Text,Qt::white);
    ui->position->setPalette(*palet);
    ui->duration->setPalette(*palet);
    ui->position->setReadOnly(true);
    ui->duration->setReadOnly(true);
    ui->position->setText("00:00");
    ui->duration->setText("00:00");
    ui->position->setAlignment(Qt::AlignCenter);
    ui->duration->setAlignment(Qt::AlignCenter);

    ui->add_button->setStyleSheet(customization::getMenuStyleSheet());
    ui->mute_button->setStyleSheet(customization::getMuteStyleSheet());
    ui->next_button->setStyleSheet(customization::getNextStyleSheet());
    ui->pause_button->setStyleSheet(customization::getPauseStyleSheet());
    ui->play_button->setStyleSheet(customization::getPlayStyleSheet());
    ui->previous_button->setStyleSheet(customization::getPreviousStyleSheet());
    ui->stop_button->setStyleSheet(customization::getStopStyleSheet());
    this->setStyleSheet(customization::getWindowStyleSheet());
    ui->progress_slider->setStyleSheet(customization::getSliderStyleSheet());
    ui->volume_slider->setStyleSheet(customization::getSliderStyleSheet());


    videoWidget->hide();

    this->adjustSize();

}

/*
* AALTO C++ media_player_8
* @function_type: Destructor
* @desc: Deletes the object
* @param: None
* @return: void
*/
video_player::~video_player()
{
    delete ui;
    delete playlist;
    delete player;
    delete videoWidget;
    delete palet;
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Adds videos to the playlist
* @param: None
* @return: void
*/
void video_player::on_add_button_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Select file(s) to add", "", "Video format (*.wmv)");
    for (auto file : files) {
        playlist->addMedia(QUrl::fromLocalFile(file));
    }
    playlist->setCurrentIndex(0);
    player->setMedia(playlist->currentMedia());
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Mutes the volume
* @param: None
* @return: void
*/
void video_player::on_mute_button_clicked()
{
    if (!player->isMuted()) {
        player->setMuted(true);
        ui->mute_button->setText("Unmute");
    }
    else {
        player->setMuted(false);
        ui->mute_button->setText("Mute");
    }
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Plays the video
* @param: None
* @return: void
*/
void video_player::on_play_button_clicked()
{
    if (!playlist->isEmpty())
    {
        videoWidget->show();
        player->play();
    }
    else
        qDebug() << "Playlist empty";
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Pauses the video
* @param: None
* @return: void
*/
void video_player::on_pause_button_clicked()
{
    if (!playlist->isEmpty())
        player->pause();
    else
        qDebug() << "Playlist empty";
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Stops the video
* @param: None
* @return: void
*/
void video_player::on_stop_button_clicked()
{
    if (!playlist->isEmpty())
        player->stop();
    else
        qDebug() << "Playlist empty";
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Plays the previous video in playlist
* @param: None
* @return: void
*/
void video_player::on_previous_button_clicked()
{
    if (!playlist->isEmpty()) {
        if (player->position() >= 3000)
            player->setPosition(0);
        else {
            playlist->previous();
            player->setMedia(playlist->currentMedia());
            player->play();
        }
    }
    else
        qDebug() << "Playlist empty";
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Plays the next video in playlist
* @param: None
* @return: void
*/
void video_player::on_next_button_clicked()
{
    if (!playlist->isEmpty()) {
        playlist->next();
        player->setMedia(playlist->currentMedia());
        player->play();
    }
    else
        qDebug() << "Playlist empty";
}

/*
* AALTO C++ media_player_8
* @function_type: Drag and drop function
* @desc: Drag and drop enter event
* @param: event
* @return: void
*/
void video_player::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

/*
* AALTO C++ media_player_8
* @function_type: Drag and drop function
* @desc: Drag an drop drop event
* @param: event
* @return: void
*/
void video_player::dropEvent(QDropEvent *event)
{
    QList<QUrl> urlList = event->mimeData()->urls();
    for (auto url : urlList) {
        std::string urlString = url.toString().toStdString();
        std::string format = urlString.substr(urlString.length()-3,3);
        if (format == "wmv")
            playlist->addMedia(url);
        else
            qDebug() << "Wrong format";
    }
    if (!playlist->isEmpty()) {
        playlist->setCurrentIndex(0);
        player->setMedia(playlist->currentMedia());
    }
}

/*
* AALTO C++ media_player_8
* @function_type: Helper function
* @desc: Converts milliseconds to hh:mm:ss
* @param: position
* @return: The converted time as Qstring
*/
QString converter2(int position)
{
    int s_total = position/1000;
    int h = s_total/3600;
    int m = s_total/60 % 60;
    int s = s_total % 60;
    QString sString = QString::number(s);
    QString mString = QString::number(m);
    if (m <= 9)
        mString.prepend("0");
    if (s <= 9)
        sString.prepend("0");
    if (h > 0) {
        QString hString = QString::number(h);
        return QString(hString+":"+mString+":"+sString);
    }
    else return QString(mString+":"+sString);
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Updates the position of the video
* @param: position
* @return: void
*/
void video_player::on_positionChanged(int position)
{
    ui->progress_slider->setValue(position);
    ui->position->setText(converter2(position));
}

/*
* AALTO C++ media_player_8
* @function_type: Ui function
* @desc: Updates the duration of the video
* @param: position
* @return: void
*/
void video_player::on_durationChanged(int position)
{
    ui->progress_slider->setMaximum(position);
    ui->duration->setText(converter2(position));
}
