#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <QDialog>
#include <QtDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QNetworkRequest>
#include <QMediaContent>
#include <QLCDNumber>
#include <QWidget>
#include <QPoint>
#include <QStandardItemModel>
#include <QTimer>
#include <QAction>
#include <QMenu>
#include <QSignalMapper>
#include <QInputDialog>
#include <QGraphicsDropShadowEffect>
#include "playlist.h"
#include "song.h"
#include "video_player.h"

namespace Ui {
class media_player;
}

class media_player : public QDialog
{
    Q_OBJECT

public:
    /*
    * AALTO C++ media_player_8
    * @function_type: Constructor
    * @desc:
    * @param:
    * @return:
    */
    explicit media_player(QWidget *parent = nullptr);

    /*
    * AALTO C++ media_player_8
    * @function_type: Destructor
    * @desc:
    * @param:
    * @return:
    */
    ~media_player();

    /*
    * AALTO C++ media_player_8
    * @function_type: void
    * @desc: when the play button is clicked
    * this function is called and the playlist is set on cyclic-loop player mode
    * meaning it will all the instances in playlist
    * @param:
    * @return:
    */
    void setThisSongOnPlayback(Song &song);

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void resetVisualPlaylist(unsigned int signal);

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void setPlayback();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    playlist* getPlaylist() { return musicPlaylist; }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void update_album_art(Song &song);

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    bool checkPlaybackPosition(unsigned int index) { return musicPlaylist->getPlaybackControl().getPosition() == index; }
private slots:
    void reject();

    void on_progress_slider_sliderMoved(int position);

    void on_volume_slider_sliderMoved(int position);

    void on_play_button_clicked();

    void on_pause_button_clicked();

    void on_stop_button_clicked();

    void on_durationChanged(int position);

    void on_positionChanged(int position);

    void on_button_file_clicked();

    void on_button_previous_clicked();

    void on_button_next_clicked();

    void on_button_shuffle_clicked();

    void on_button_minimize_clicked(); 

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

    void time_passed(int position);

    void time_to_end(int position);

    void playback_time_state_control();

    QString converter(int position);

    void on_mute_butten_clicked();

    void on_video_button_clicked();

    //void update_album_art(Song song);

    void customContextMenuForPlaylistSorting(QPoint position);

    void customContextMenuForMetadataEdit(QPoint position);

    void sortByArtist();

    void sortByAlbum();

    void sortAlpabetically();

    void deleteContentOfPlaylist();

    void changeNameOfMedia(int row);

    void changeNameOfTheArtist(int row);

    void changeNameOfTheRelease(int row);

    void deleteSelectedSong(int row);

private:
    playlist *musicPlaylist;
    Ui::media_player *ui;
    QStandardItemModel *visualPlaylistMOdel;
    QMediaPlayer *player;
    QTimer *playbackTimer;
    bool is_minimized = false;
    QPoint pos_;
    video_player *videoPlayer;
    QGraphicsDropShadowEffect *shadowEffect;
    QPalette *palet;
    QPixmap *default1;


    void addSongsByFilename(QStringList filenames);
    void loadDefaultMP3Library();
    QMenu *metadataContextmenu;
    QMenu *playlistContextMenu;
    QAction *artistSort;
    QAction *albumSort;
    QAction *alphabetSort;
    QAction *clear;
    QAction *editSongName;
    QAction *editArtist;
    QAction *editAlbum;
    QAction *deleteSong;
    QAction *giveCustomHashtag;
    QSignalMapper *mapperForNameChange;
    QSignalMapper *mapperForArtistChange;
    QSignalMapper *mapperForAlbumChange;
    QSignalMapper *mapperForErasing;

    friend class Tester;
};

#endif // MEDIA_PLAYER_H
