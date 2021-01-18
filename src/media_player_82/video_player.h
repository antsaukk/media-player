#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QFileDialog>
#include <QtGui>

namespace Ui {
class video_player;
}

class video_player : public QWidget
{
    Q_OBJECT

public:
    /*
    * AALTO C++ media_player_8
    * @function_type: Constructor
    * @desc: Constructs the object
    * @param: parent
    * @return: The constructed object
    */
    explicit video_player(QWidget *parent = nullptr);

    /*
    * AALTO C++ media_player_8
    * @function_type: Destructor
    * @desc: Deletes the object
    * @param: None
    * @return: void
    */
    ~video_player();

    /*
    * AALTO C++ media_player_8
    * @function_type: Drag and drop function
    * @desc: Drag and drop enter event
    * @param: event
    * @return: void
    */
    void dragEnterEvent(QDragEnterEvent *event);

    /*
    * AALTO C++ media_player_8
    * @function_type: Drag and drop function
    * @desc: Drag an drop drop event
    * @param: event
    * @return: void
    */
    void dropEvent(QDropEvent *event);

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Updates the duration of the video
    * @param: position
    * @return: void
    */
    void on_durationChanged(int position);

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Updates the position of the video
    * @param: position
    * @return: void
    */
    void on_positionChanged(int position);

signals:

public slots:

private slots:

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Adds videos to the playlist
    * @param: None
    * @return: void
    */
    void on_add_button_clicked();

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Mutes the volume
    * @param: None
    * @return: void
    */
    void on_mute_button_clicked();

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Plays the video
    * @param: None
    * @return: void
    */
    void on_play_button_clicked();

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Pauses the video
    * @param: None
    * @return: void
    */
    void on_pause_button_clicked();

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Stops the video
    * @param: None
    * @return: void
    */
    void on_stop_button_clicked();

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Plays the previous video in playlist
    * @param: None
    * @return: void
    */
    void on_previous_button_clicked();

    /*
    * AALTO C++ media_player_8
    * @function_type: Ui function
    * @desc: Plays the next video in playlist
    * @param: None
    * @return: void
    */
    void on_next_button_clicked();

private:
    Ui::video_player *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QVideoWidget *videoWidget;
    QPalette *palet;
};

#endif // VIDEO_PLAYER_H
