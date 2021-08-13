/*
* AALTO C++ media_player_8
* @class_name:
* @description:
* @version:
* @authors: @henrik, @antsaukk, @miikka
*/

#include <QtCore>
#include <QtGui>
#include <iostream>
#include <QSizePolicy>
#include <QSize>
#include <QWidget>
#include <QDesktopWidget>
#include <QTableWidget>
#include <QLabel>
#include <QDesktopWidget>
#include <QScreen>
#include <QFileDialog>
#include <QDir>
#include <thread>
#include <QPalette>
#include <QByteArray>
#include "customization.h"
#include "media_player.h"
#include "media_player.h"
#include "media_player.h"
#include "media_player.h"
#include "ui_media_player.h"


media_player::media_player(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::media_player)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet(customization::getWindowStyleSheet());    //style of widget
    shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9);
    shadowEffect->setOffset(10);
    visualPlaylistMOdel = new QStandardItemModel(this);
    ui->playlistView->setModel(visualPlaylistMOdel);
    visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Load music here") << tr("File path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);
    ui->button_next->setStyleSheet(customization::getNextStyleSheet());
    ui->label->setStyleSheet(customization::getLabelStyleSheet());
    ui->button_previous->setStyleSheet(customization::getPreviousStyleSheet());
    ui->stop_button->setStyleSheet(customization::getStopStyleSheet());
    ui->play_button->setStyleSheet(customization::getPlayStyleSheet());
    ui->pause_button->setStyleSheet(customization::getPauseStyleSheet());
    ui->button_file->setStyleSheet(customization::getMenuStyleSheet());
    ui->button_shuffle->setStyleSheet(customization::getShuffleStyleSheet());
    ui->button_minimize->setStyleSheet(customization::getMinimizationStyleSheet());
    ui->playlistView->setStyleSheet(customization::getTableViewStyleSheet());
    ui->playlistView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->playlistView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->mute_butten->setStyleSheet(customization::getMuteStyleSheet());
    ui->video_button->setStyleSheet(customization::getVideoStyleSheet());

    player = new QMediaPlayer(this);
    musicPlaylist = new playlist;
    playbackTimer = new QTimer(this);
    this->adjustSize();



    connect(player, &QMediaPlayer::positionChanged, this, &media_player::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &media_player::on_durationChanged);
    connect(playbackTimer, SIGNAL(timeout()), this, SLOT(playback_time_state_control()));
    connect(ui->playlistView, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customContextMenuForMetadataEdit(QPoint)));
    connect(ui->playlistView->horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customContextMenuForPlaylistSorting(QPoint))); //new
    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){ //lambda expression to catch up the index of song from QTable
        auto invokedPlaylist = musicPlaylist->getPlayList();
        unsigned int invokedIndex = unsigned(index.row());
        musicPlaylist->resetPlaybackControl(invokedIndex);
        setThisSongOnPlayback(invokedPlaylist[invokedIndex]);
    });

    palet = new QPalette();
    palet->setColor(QPalette::Text,Qt::white);
    ui->lineEdit->setPalette(*palet);
    ui->lineEdit_2->setPalette(*palet);

    ui->play_button->setPalette(*palet);
    this->window()->setLayout(ui->all_labels);
    setAcceptDrops(true); // For drag-and-drop functionality

    ui->video_button->setPalette(*palet);
    ui->video_button->setText("VideoPlayer");

    ui->mute_butten->setPalette(*palet);
    ui->mute_butten->setText("Mute");
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);

    Q_INIT_RESOURCE(res);
    default1 = new QPixmap(":/new/prefix1/no-music.png");
    ui->label->setPixmap(default1->scaled(ui->label->size()*3+QSize(0,300),Qt::KeepAspectRatio));

    ui->lineEdit->setText("00:00");
    ui->lineEdit_2->setText("00:00");
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit_2->setAlignment(Qt::AlignCenter);
    this->pos_ = QWidget::mapFromGlobal(this->pos());

    ui->progress_slider->setStyleSheet(customization::getSliderStyleSheet());
    ui->volume_slider->setStyleSheet(customization::getSliderStyleSheet());

    videoPlayer = new video_player();

    loadDefaultMP3Library();

    /*
    * allocation of assessors for sorting functions
    * of playlist from context menu
    */
    playlistContextMenu = new QMenu(this);
    artistSort = new QAction(tr("Sort by Artist"), this);
    albumSort = new QAction(tr("Sort by Album"), this);
    alphabetSort = new QAction(tr("Sort alphabetically"), this);
    clear = new QAction(tr("Delete all songs"), this);
    playlistContextMenu->addAction(artistSort);
    playlistContextMenu->addAction(albumSort);
    playlistContextMenu->addAction(alphabetSort);
    playlistContextMenu->addAction(clear);
    connect(artistSort, &QAction::triggered, this, &media_player::sortByArtist);
    connect(albumSort, &QAction::triggered, this, &media_player::sortByAlbum); //write exceptions if there is no such metadata
    connect(alphabetSort, &QAction::triggered, this, &media_player::sortAlpabetically);
    connect(clear, &QAction::triggered, this, &media_player::deleteContentOfPlaylist);


}

/*
* AALTO C++ media_player_8
* @function_type: Destructor
* @desc:
* @param:
* @return:
*/
media_player::~media_player()
{
    delete ui;
    delete musicPlaylist;
    delete visualPlaylistMOdel;
    delete player;
    delete playbackTimer;
    delete shadowEffect;
    delete default1;
    delete palet;
    delete videoPlayer;// Destruct video player as well if it's hidden
}

void media_player::reject()
{
    qApp->exit();
}

void media_player::addSongsByFilename(QStringList filenames)
{
    for(auto i : filenames)
    {

#ifdef Q_OS_UNIX
        Song song(QUrl::fromLocalFile(i));
#else
        QFileInfo file_info = QFileInfo(i);
        QString fullFileName = file_info.absoluteFilePath();
        Song song(fullFileName);
#endif

        musicPlaylist->addMediaItem(song);
        QString setInVisualTable = QString::fromStdString(song.getID3Tag().getArtist() +
                                                          " - " + song.getID3Tag().getSongName());
        std::cout << setInVisualTable.toStdString() << std::endl;
        QList <QStandardItem*> listOfSongNames;
        listOfSongNames.append(new QStandardItem(setInVisualTable));
        visualPlaylistMOdel->appendRow(listOfSongNames);
    }
}

void media_player::loadDefaultMP3Library()
{
    QString defaultDirectory = QCoreApplication::applicationDirPath() + "/" + "Music";
    QDir dir(defaultDirectory);
    QStringList filenames = dir.entryList(QStringList() << "*.mp3" << "*.MP3", QDir::Files);
    qDebug() << filenames.length();
    for (int i = 0; i < filenames.length(); i++) {
        filenames[i] = defaultDirectory + "/" + filenames[i];
    }
    addSongsByFilename(filenames);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::playback_time_state_control()
{
    if (player->mediaStatus() == 7) setPlayback();
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::customContextMenuForMetadataEdit(QPoint position)
{
    QModelIndex selectedRowIndex = ui->playlistView->indexAt(position);
    int row = selectedRowIndex.row();
    metadataContextmenu = new QMenu(this);
    editSongName = new QAction(tr("Edit Song Name"), this);
    editArtist = new QAction(tr("Edit Artist Name"), this);
    editAlbum = new QAction(tr("Edit Album Name"), this);
    deleteSong = new QAction(tr("Delete song from playlist"), this);
    giveCustomHashtag = new QAction(tr("Give a song custom hashtag"), this);
    metadataContextmenu->addAction(editSongName);
    metadataContextmenu->addAction(editArtist);
    metadataContextmenu->addAction(editAlbum);
    metadataContextmenu->addAction(deleteSong);
    metadataContextmenu->addAction(giveCustomHashtag);
    mapperForNameChange = new QSignalMapper(this);
    mapperForArtistChange = new QSignalMapper(this);
    mapperForAlbumChange = new QSignalMapper(this);
    mapperForErasing = new QSignalMapper(this);
    mapperForNameChange->setMapping(editSongName, row);
    mapperForArtistChange->setMapping(editArtist, row);
    mapperForAlbumChange->setMapping(editAlbum, row);
    mapperForErasing->setMapping(deleteSong, row);
    connect(editSongName, SIGNAL(triggered()), mapperForNameChange, SLOT(map()));
    connect(editArtist, SIGNAL(triggered()), mapperForArtistChange, SLOT(map()));
    connect(editAlbum, SIGNAL(triggered()), mapperForAlbumChange, SLOT(map()));
    connect(deleteSong, SIGNAL(triggered()), mapperForErasing, SLOT(map()));
    connect(mapperForNameChange, SIGNAL(mapped(int)), this, SLOT(changeNameOfMedia(int)));
    connect(mapperForArtistChange, SIGNAL(mapped(int)), this, SLOT(changeNameOfTheArtist(int)));
    connect(mapperForAlbumChange, SIGNAL(mapped(int)), this, SLOT(changeNameOfTheRelease(int)));
    connect(mapperForErasing, SIGNAL(mapped(int)), this, SLOT(deleteSelectedSong(int)));
    metadataContextmenu->popup(ui->playlistView->viewport()->mapToGlobal(position));
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::changeNameOfMedia(int invokedRowIndex)
{
    if (musicPlaylist->getLength() > 0 || invokedRowIndex >= 0) {
        bool checkUserInput;
        QString userInput = QInputDialog::getText(this, tr("EDIT NAME"), tr("Enter song name below"), QLineEdit::Normal,
                                             "", &checkUserInput);
        if (checkUserInput && !userInput.isEmpty()){
            std::string updatedSongName = userInput.toStdString();
            auto mediaObjectToBeChanged = musicPlaylist->getPlayList()[unsigned(invokedRowIndex)];
            mediaObjectToBeChanged.getID3Tag().setSongName(updatedSongName);
            resetVisualPlaylist(7);
        }
    } else qDebug() << "Invoked index is invalid or playlist is empty!";
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::changeNameOfTheArtist(int invokedRowIndex)
{
    if (musicPlaylist->getLength() > 0 || invokedRowIndex >= 0) {
        bool checkUserInput;
        QString userInput = QInputDialog::getText(this, tr("EDIT ARTIST"), tr("Enter artist name below"), QLineEdit::Normal,
                                             "", &checkUserInput);
        if (checkUserInput && !userInput.isEmpty()){
            std::string updatedArtistName = userInput.toStdString();
            auto mediaObjectToBeChanged = musicPlaylist->getPlayList()[unsigned(invokedRowIndex)];
            mediaObjectToBeChanged.getID3Tag().setArtist(updatedArtistName);
            resetVisualPlaylist(7);
        }
    } else qDebug() << "Invoked index is invalid or playlist is empty!";

}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::changeNameOfTheRelease(int invokedRowIndex)
{
    if (musicPlaylist->getLength() > 0 || invokedRowIndex >= 0) {
        bool checkUserInput;
        QString userInput = QInputDialog::getText(this, tr("EDIT RELEASE"), tr("Enter album name below"), QLineEdit::Normal,
                                             "", &checkUserInput);
        if (checkUserInput && !userInput.isEmpty()){
            std::string updatedAlbumName = userInput.toStdString();
            auto mediaObjectToBeChanged = musicPlaylist->getPlayList()[unsigned(invokedRowIndex)];
            mediaObjectToBeChanged.getID3Tag().setAlbum(updatedAlbumName);
            if (checkPlaybackPosition(unsigned(invokedRowIndex))){
                auto song = musicPlaylist->getPlayList()[unsigned(invokedRowIndex)];
                const char *labelToSet = song.getID3Tag().getAlbum().c_str();
                visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Album playing: ") + tr(labelToSet));
            }
        }
    } else qDebug() << "Invoked index is invalid or playlist is empty!";
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc: check if the song is still on playback
* @param:
* @return:
*/
void media_player::deleteSelectedSong(int invokedRowIndex)
{
    if (musicPlaylist->getLength() > 0 || invokedRowIndex >= 0){
        if (checkPlaybackPosition(unsigned(invokedRowIndex))) {
            player->stop();
            auto songToRemove = musicPlaylist->getPlayList()[unsigned(invokedRowIndex)];
            musicPlaylist->removeMediaItem(songToRemove);
            musicPlaylist->resetPlaybackControl(0);
            resetVisualPlaylist(6);
        } else {
            auto songToRemove = musicPlaylist->getPlayList()[unsigned(invokedRowIndex)];
            musicPlaylist->removeMediaItem(songToRemove);
            resetVisualPlaylist(7);
        }
    } else qDebug() << "Invoked index is invalid or playlist is empty!";
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::customContextMenuForPlaylistSorting(QPoint position)
{
    playlistContextMenu->popup(ui->playlistView->horizontalHeader()->viewport()->mapToGlobal(position));
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::sortByArtist()
{
    player->stop();
    musicPlaylist->orderPlaylistByArtist();
    resetVisualPlaylist(1);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::sortByAlbum()
{
    player->stop();
    musicPlaylist->orderPlaylistByRelease();
    resetVisualPlaylist(2);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::sortAlpabetically()
{
    player->stop();
    musicPlaylist->orderPlaylistAlphabeticallyBySongName();
    resetVisualPlaylist(3);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::deleteContentOfPlaylist()
{
    player->stop();
    musicPlaylist->clearPlaylist();
    resetVisualPlaylist(4);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::on_progress_slider_sliderMoved(int position)
{
    player->setPosition(position);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::on_volume_slider_sliderMoved(int position)
{
    player->setVolume(position);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::on_play_button_clicked()
{
    if (musicPlaylist->getLength() > 0)
    {
        if (player->state() == 2)
        {
            player->play();
        }
        else if(player->state() != 1)
        {
            auto songs = musicPlaylist->getPlayList();
            auto index = musicPlaylist->getPlaybackControl().getPosition();
            setThisSongOnPlayback(songs[index]);
            qDebug()<<player->errorString();
        }
    }
    else
    {
        qDebug()<<"Playlist empty";
    }
}

// pause music
void media_player::on_pause_button_clicked()
{
    player->pause();
}

// stop music
void media_player::on_stop_button_clicked()
{
    player->stop();
}

// set max value for progress slider
void media_player::on_durationChanged(int position)
{
    ui->progress_slider->setMaximum(position);
    time_to_end(position);
}

// control the proggress slider
void media_player::on_positionChanged(int position)
{
    ui->progress_slider->setValue(position);
    time_passed(position);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::on_button_file_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,"Select one or more files to playlist","/Users", "Music (*.mp3)");
    addSongsByFilename(filenames);

    visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Track name"));
}

void media_player::setThisSongOnPlayback(Song &song)
{
    if (musicPlaylist->getLength() > 0)
    {
        player->setMedia(song);
        if (song.getID3Tag().getAlbum() != "No value found") {
            const char *labelToSet = song.getID3Tag().getAlbum().c_str();
            visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Album playing: ") + tr(labelToSet));
        }
        else visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Track name"));
        player->play();
        playbackTimer->start(1000);
    }
    else
    {
        qDebug()<<"Playlist empty";
    }
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::setPlayback()
{
    auto index = musicPlaylist->next();
    auto songs = musicPlaylist->getPlayList();
    player->setMedia(songs[index]);
    if (songs[index].getID3Tag().getAlbum() != "No value found") {
        const char *labelToSet = songs[index].getID3Tag().getAlbum().c_str();
        visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Album playing:") + tr(labelToSet));
    }
    else visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Track name"));
    player->play();
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc: If over 3 seconds has passed, replay the same song, Otherwise play the previous song
* @param:
* @return:
*/
void media_player::on_button_previous_clicked()
{
    if (musicPlaylist->getLength() > 0)
    {
        if (player->position() >= 3000) {
            player->setPosition(0);
        }
        else {
            auto index = musicPlaylist->back();
            auto songs = musicPlaylist->getPlayList();
            setThisSongOnPlayback(songs[index]);
        }
    }
    else
    {
        qDebug()<<"Playlist empty";
    }
}
/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::on_button_next_clicked()
{
    if (musicPlaylist->getLength() > 0)
    {
        auto index = musicPlaylist->next();
        auto songs = musicPlaylist->getPlayList();
        setThisSongOnPlayback(songs[index]);
    }
    else
    {
        qDebug()<<"Playlist empty";
    }
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::resetVisualPlaylist(unsigned int signal)
{
    visualPlaylistMOdel->clear();
    switch(signal){
    case (1):
        visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Sorted by Artist"));
        break;
    case (2):
        visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Sorted by Album"));
        break;
    case(3):
        visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Sorted Alphabetically"));
        break;
    case (4):
        visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Load music here"));
        break;
    case(5):
        visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Shuffled"));
        break;
    case(6):
        visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Track Name"));
        break;
    case(7):
        auto index = musicPlaylist->getPlaybackControl().getPosition();
        auto songs = musicPlaylist->getPlayList();
        if (songs[index].getID3Tag().getAlbum() != "No value found") {
            const char *labelToSet = songs[index].getID3Tag().getAlbum().c_str();
            visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Album playing:") + tr(labelToSet));
        }
        else visualPlaylistMOdel->setHorizontalHeaderLabels(QStringList() << tr("Track name"));
        break;
    }
    if (musicPlaylist->getLength() > 0) {
        auto songsContainer = musicPlaylist->getPlayList();
        for (auto song : songsContainer)
        {
            QString metaDataToSet = QString::fromStdString(song.getID3Tag().getArtist() +
                                                                                " - " + song.getID3Tag().getSongName());
            QList <QStandardItem*> listOfContent;
            listOfContent.append(new QStandardItem(metaDataToSet));
            visualPlaylistMOdel->appendRow(listOfContent);
        }
    }
    else qDebug() << "No songs in playlist!";
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
void media_player::on_button_shuffle_clicked()
{
    player->stop();
    musicPlaylist->shuffleList();
    resetVisualPlaylist(5);
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc: Control the minituratisation on the media player
* In mini-mode only the necessary botton are showing and windowis
* moved top lef of the screen and the window cannot be scaled
* @param:
* @return:
*/
void media_player::on_button_minimize_clicked()
{

    if (!is_minimized)
    {
        ui->button_minimize->setStyleSheet(customization::getMaximizationStyleSheet());
        this->setFixedSize(650,40);
        this->move(this->rect().topLeft());
        this->adjustSize();
        is_minimized = true;
    }
    else
    {

        ui->button_minimize->setStyleSheet(customization::getMinimizationStyleSheet());
        this->move(this->pos_);//täää
        this->setMinimumSize(409,100);
        this->setMaximumSize(700,700);
        this->move(this->rect().center());
        this->adjustSize();
        is_minimized = false;
    }

}

void media_player::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void media_player::dropEvent(QDropEvent *event)
{
    QList<QUrl> urlList = event->mimeData()->urls();
    for (auto url : urlList) {
        Song song(url);
        musicPlaylist->addMediaItem(song);
        QString setInVisualTable = QString::fromStdString(song.getID3Tag().getArtist() +
                                                          " - " + song.getID3Tag().getSongName());
        QList <QStandardItem*> listOfSongNames;
        listOfSongNames.append(new QStandardItem(setInVisualTable));
        visualPlaylistMOdel->appendRow(listOfSongNames);
        musicPlaylist->printOrderedPlaylist(1); 
    }
}

QString media_player::converter(int position)
{
    int all_sek = position/100;
    int min = all_sek / 10 / 60;
    int sek = all_sek /10 % 60;
    int sek_s = all_sek % 100;
    QString sekS = QString::number(sek);
    QString minS = QString::number(min);
    QString sek_sS = QString::number(sek_s);
    if (sekS.length() == 1)
    {
        sekS.prepend("0");
    }
    if (minS.length() == 1)
    {
        minS.prepend("0");
    }
    if (sek_sS.length() == 1)
    {
        sek_sS.prepend("0");
    }
    return QString(minS+":"+sekS+":"+sek_sS);
}

void media_player::time_passed(int position)
{
    ui->lineEdit_2->setText(converter(position));
}

void media_player::time_to_end(int position)
{
    ui->lineEdit->setText(converter(position));
}

void media_player::on_mute_butten_clicked()
{
    std::cout<<"mute pressed"<<std::endl;
    if(!player->isMuted())
    {
        player->setMuted(true);
    }
    else
    {
        player->setMuted(false);
    }
}

void media_player::on_video_button_clicked()
{
    if(videoPlayer->isHidden())
    {
        videoPlayer->show();
    }
    else
    {
        videoPlayer->hide();
    }
}

void media_player::update_album_art(Song &song)
{
    std::string pic_s = song.getID3Tag().getFrameValue("APIC");
    const char *pic_c = pic_s.c_str();
    if(pic_s != "No value found")
    {
        QPixmap pic;
        QByteArray arr(pic_c);
        pic.loadFromData(arr);
        ui->label->setPixmap(pic);
    }
}
