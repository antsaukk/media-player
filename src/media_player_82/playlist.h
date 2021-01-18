/*
* AALTO C++
* playlist interface
* @description: header file for playlist.cpp
* which contains interface, consisting of two classes
* playlist, playlistIterator
* @author: @antsaukk
* @version: 1.0
* by: group media_player_8
*/

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QMediaContent>
#include <QMediaPlaylist>
#include <QStringList>
#include <vector>
#include <string>
#include "song.h" 

class playlistIterator
{
public:
    /*
    * AALTO C++ media_player_8
    * @function_type: Constructor
    * @desc:
    * @param:
    * @return:
    */
    playlistIterator()
    {
        min_value = 0;
        iterator_index = 0;
        flag = 0;
    }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int getPosition() const { return iterator_index; }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int getFlag() const { return flag; }

    /* LEFT FOR FUTURE INMPLEMENTATION - NOT USED IN THIS CONTEXT
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int getMaxPositionIndex() const { return max_value; }

    /* LEFT FOR FUTURE INMPLEMENTATION - NOT USED IN THIS CONTEXT
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int getMinPositionIndex() const { return min_value; }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int stepForward();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int stepBack();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void updateMaxValue(unsigned int lengthOfPlaylist) { max_value = lengthOfPlaylist - 1; }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void updateIterationVariable(unsigned int position) { iterator_index = position; }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void updateFlag(unsigned int signal){ flag = signal; }

protected:
    unsigned int max_value;
    unsigned int min_value;
private:
    unsigned int iterator_index;
    unsigned int flag;
    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    bool playbackIndexController();
};

class playlist : public QMediaPlaylist
{
    Q_OBJECT
public:
    /*
    * AALTO C++ media_player_8
    * @function_type: Constructor
    * @desc: constructs new playlist object
    * @param: name of playlist
    */
    playlist(const std::string &nameOfPlayList = "default");

    /* LEFT FOR FUTURE INMPLEMENTATION - NOT USED IN THIS CONTEXT
    * AALTO C++ media_player_8
    * @function_type: constant song getter
    * @desc: getter function for particular song
    * finds song in the playlist by name and returns
    * @param: const string songName
    * @return: the required song if if found
    * otherwise throws an exception "No song with the required name found"
    */
    Song getSong(const std::string &songName) const;

    /*
    * AALTO C++ media_player_8
    * @function_type: void
    * @desc: add the song object to the playlist
    * @param: song which has to be added
    * @return:
    */
    void addMediaItem(Song &song);

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    bool removeMediaItem(Song &song);

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int next();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int back();

    /*
    * AALTO C++ media_player_8
    * @function_type: bool
    * @desc: deletes all content from the current playlist
    * @param:
    * @return: true if playlist is cleared, otherwise false
    */
    bool clearPlaylist();

    /*
    * AALTO C++ media_player_8
    * @function_type: void
    * @desc: testing
    * @param:
    * @return:
    */
    void printPlaylist();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void updateTheLengthOfPlaylist(int factor);

    /*
    * AALTO C++ media_player_8
    * @function_type: std::vector <Song>
    * @desc: getter function for songs container
    * @param:
    * @return: playlist of the player with songs
    */
    std::vector<Song> getPlayList() const { return playlistOfSongsObjects; }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    unsigned int getLength() const { return lengthOfPlaylist; }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    playlistIterator getPlaybackControl() const { return playbackIterator; }

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void orderPlaylistByArtist();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void orderPlaylistAlphabeticallyBySongName();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void orderPlaylistByRelease();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void printOrderedPlaylist(unsigned int n);

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void shuffleList();

    /*
    * AALTO C++ media_player_8
    * @function_type:
    * @desc:
    * @param:
    * @return:
    */
    void resetPlaybackControl(unsigned int invokedIndex) { playbackIterator.updateIterationVariable(invokedIndex); }
protected:
    unsigned int lengthOfPlaylist;
private:
    std::vector<Song> playlistOfSongsObjects;
    std::string nameOfPlaylist;
    playlistIterator playbackIterator;
    unsigned int nullIteration;
};

#endif // PLAYLIST_H
