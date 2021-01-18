/*
* AALTO C++ media_player_8
* @class_name: playlist.cpp
* @description: .cpp file for playlist class
* holds necessary functions needed to manipulate the
* playlist object and control its iteration variable in order to avoid memory problems
* @version: 1.0
* @author: @antsaukk
*/

#include <QFileDialog>
#include <QDir>
#include <iostream>
#include <vector>
#include <algorithm>
#include "playlist.h"

/*
* AALTO C++ media_player_8
* @function_type: Constructor
* @desc: give implicit name for playlist (for future purposes it is made so that
* it can give custom name,but not implemted here)
* @param: const string (reference) name (not needed in this version)
* @return: nothing
*/
playlist::playlist(const std::string &name)
{
    nameOfPlaylist = name;
    lengthOfPlaylist = 0;
    nullIteration = 0;
}

/*
* AALTO C++ media_player_8
* @function_type: Adder functionund
* @desc: , required for adding the songs to playlist container
* after each addition updated the length of playlist by 1 in order to keep track on the upper and lower bound
* @param: reference to the song object.
* @return: nothing
*/
void playlist::addMediaItem(Song &song)
{
    playlistOfSongsObjects.push_back(song);
    updateTheLengthOfPlaylist(1);
}

/*
* AALTO C++ media_player_8
* @function_type: iteration function
* @desc: performs playlist iteration on one step forward through
* the pointer arithmetics implented in class playlist iterator
* @param: none
* @return: updated iteration variable
*/
unsigned int playlist::next()
{
    playbackIterator.updateFlag(1);
    playbackIterator.stepForward();
    return playbackIterator.getPosition();
}

/*
* AALTO C++ media_player_8
* @function_type: iteration function
* @desc: performs playlist iteration one step back through
* the pointer arithmetics implemented in class playlist iterator
* @param: none
* @return: updated position of iterator variable
*/
unsigned int playlist::back()
{
    playbackIterator.updateFlag(0);
    playbackIterator.stepBack();
    return playbackIterator.getPosition();
}

/*
* AALTO C++ media_player_8
* @function_type: remover function
* @desc: removes a song from the playlist container.
* Receives song object invoked from Playlist visualtable and gives it as an argument to this function
* Compares the named of invoked song and actual song in container and if they match preformes removing
* @param: reference to song to be removed
* @return: true if song is removed, false if not
*/
bool playlist::removeMediaItem(Song &songToRemove)
{
    for (auto song = playlistOfSongsObjects.begin(); song != playlistOfSongsObjects.end(); song++)
    {
        if (song->getID3Tag().getSongName() == songToRemove.getID3Tag().getSongName()){
            playlistOfSongsObjects.erase(song);
            updateTheLengthOfPlaylist(-1);
            return true;
        }
    }
//    qDebug() << "error, song name is not matching";
    return false;
}

/*
* AALTO C++ media_player_8
* @function_type: cleaner function
* @desc: deletes all content of playlist
* @param: none
* @return: true if playlist is cleared, false if it has been already empty
*/
bool playlist::clearPlaylist()
{
    if (lengthOfPlaylist > 0) {
        updateTheLengthOfPlaylist(int(-lengthOfPlaylist));
        playlistOfSongsObjects.clear();
        printPlaylist(); //testing function
        return true;
    } else qDebug() << "Playlist is already empty!";
    return false;
}

/*
* AALTO C++ media_player_8
* @function_type: tester function
* @desc: prints length of playlist in order to track its size in case of incremention or decremention
* @param:
* @return:
*/
void playlist::printPlaylist()
{
    qDebug() << "length of playlist is " << lengthOfPlaylist;
}

/*
* AALTO C++ media_player_8
* @function_type: void updater function
* @desc: updates the length of playlist by certain factor
* @param: singed int factor
* @return: none
*/
void playlist::updateTheLengthOfPlaylist(int factor)
{
    //qDebug() << "before incremention length of playlist is " << lengthOfPlaylist;//test
    //qDebug() << "length of playlist is going to be changed by a factor "; //test
    lengthOfPlaylist += factor;
    //qDebug() << "after incremention length of playlist is " << lengthOfPlaylist;//test
    playbackIterator.updateMaxValue(getLength());
    if (lengthOfPlaylist == 0){
    playbackIterator.updateIterationVariable(nullIteration);
    qDebug() << "Playlist is empty";
    //qDebug() << "Now the iteration index is: " << playbackIterator.getPosition(); //test
    }
}

/*
* AALTO C++ media_player_8
* @function_type: helper function for sorting algorithms realization
* @desc: compares two elements by their "name" parameter
* @param: reference to a first song, reference to a second song
* @return: true or false depending on the result of comparison
*/
bool bySongName(Song &firstElement, Song &secondElement)
{
    return firstElement.getID3Tag().getSongName() < secondElement.getID3Tag().getSongName();
}

/*
* AALTO C++ media_player_8
* @function_type: helper function for sorting algorithms realization
* @desc: compares two elements by their "artist" parameter
* @param: reference to a first song, reference to a second song
* @return: true or false depending on the result of comparison
*/
bool byArtist(Song &firstElement, Song &secondElement)
{
    return firstElement.getID3Tag().getArtist() < secondElement.getID3Tag().getArtist();
}

/*
* AALTO C++ media_player_8
* @function_type: helper function for sorting algorithms realization
* @desc: compares two elements by their "Album" parameter
* @param: reference to a first song, reference to a second song
* @return: true or false depending on the result of comparison
*/
bool byAlbumRelease(Song &firstElement, Song &secondElement)
{
    return firstElement.getID3Tag().getAlbum() < secondElement.getID3Tag().getAlbum(); //not yet implemented
}

/*
* AALTO C++ media_player_8
* @function_type: sorting function
* @desc: sorts the content of playlist alphabetically, as a helper calls function "bySongName"
* which compares the criteria
* after sorting updates iteration variable to zero
* @param: none
* @return: nothing
*/
void playlist::orderPlaylistAlphabeticallyBySongName()
{
    if (lengthOfPlaylist > 0) {
        sort(playlistOfSongsObjects.begin(), playlistOfSongsObjects.end(), bySongName);
        playbackIterator.updateIterationVariable(nullIteration);
//        qDebug() << "Playlist is ordered by Song name";
        //qDebug() << "Now the iteration index is: " << playbackIterator.getPosition(); //test
//        qDebug() << "Playback will start from the beginning of playlist"; //test
        printOrderedPlaylist(1); //testing command
    }
    else qDebug() << "Playlist is empty, sorting is not possible";
}

/*
* AALTO C++ media_player_8
* @function_type: sorting function
* @desc: sorts the content of playlist by the name of the artist "byArtistName"
* which compares the criteria
* after sorting updates iteration variable to zero
* @param: none
* @return: nothing
*/
void playlist::orderPlaylistByArtist()
{
    if (lengthOfPlaylist > 0) {
        sort(playlistOfSongsObjects.begin(), playlistOfSongsObjects.end(), byArtist);
        playbackIterator.updateIterationVariable(nullIteration);
//        qDebug() << "Playlist is ordered by Artist";
        //qDebug() << "Now the iteration index is: " << playbackIterator.getPosition(); //test
//        qDebug() << "Playback will start from the beginning of playlist"; //test
        printOrderedPlaylist(2);
    }
    else qDebug() << "Playlist is empty, sorting is not possible";
}

/*
* AALTO C++ media_player_8
* @function_type: sorting function
* @desc: sorts the content of playlist by the name of the album "byAlbumName"
* which compares the criteria
* after sorting updates iteration variable to zero
* @param: none
* @return: nothing
*/
void playlist::orderPlaylistByRelease()
{
    if (lengthOfPlaylist > 0) {
        sort(playlistOfSongsObjects.begin(), playlistOfSongsObjects.end(), byAlbumRelease);
        playbackIterator.updateIterationVariable(nullIteration);
//        qDebug() << "Playlist is ordered by Album";
        //qDebug() << "Now the iteration index is: " << playbackIterator.getPosition(); //test
//        qDebug() << "Playback will start from the beginning of playlist"; //test
        printOrderedPlaylist(3);
    }
    else qDebug() << "Playlist is empty, sorting is not possible";
}

/*
* AALTO C++ media_player_8
* @function_type: shuffler function
* @desc: shuffles the content of playlist randomly
* functino is implemented with standard C++ algorithnm
* after shuffling updates iteration variable to zero
* @param: none
* @return: none
*/
void playlist::shuffleList()
{
    std::random_shuffle(playlistOfSongsObjects.begin(), playlistOfSongsObjects.end());
    playbackIterator.updateIterationVariable(nullIteration);
//    qDebug() << "Playlist is shuffled";
    //qDebug() << "Now the iteration index is: " << playbackIterator.getPosition(); //test
//    qDebug() << "Playback will start from the beginning of playlist"; //test

}

/*
* AALTO C++ media_player_8
* @function_type: tester function
* @desc: prints the content of playlist in order to check how the actual sorting based on certain criteria
* was performed
* @param: unsinged int n - signal parameter which determines which type of print to use
* @return: nothing
*/
void playlist::printOrderedPlaylist(unsigned int n)
{
    switch(n){
    case (1):
        for (auto i : playlistOfSongsObjects)
        {
            std::cout << i.getID3Tag().getSongName() << std::endl;
        }
        break;
    case(2):
        for (auto i : playlistOfSongsObjects)
        {
            std::cout << i.getID3Tag().getArtist() << std::endl;
        }
        break;
    case(3):
        for (auto i : playlistOfSongsObjects)
        {
            std::cout << i.getID3Tag().getArtist() << std::endl;
        }
        break;
    }
}

/*************************************playlistIterator_functions*************************************/


/*
* AALTO C++ media_player_8
* @function_type: controller function for iterator index
* @desc: receives the flag-signal from previous iteration action which detects if the playlist
* was incremented or decremented, based on this information check the current state and performs either step forward
* or step back. If playlist is on the upper bound, sets its iteration variable to zero, if on the lower, sets the iteration
* variable on in the end of the playlist
* @param: none
* @return: returs true if decremention or incremention is allowed, else returs false
*/
bool playlistIterator::playbackIndexController()
{
    switch (getFlag()) {
    case 0:
        if (iterator_index > min_value){
            //qDebug() << "current index is " << iterator_index;
            //qDebug() << "min value is " << min_value;
            return true;
        }
        return false;
    case 1:
        if (iterator_index < max_value) {
            //qDebug() << "current index is " << iterator_index;
            //qDebug() << "max value is " << max_value;
            return true;
        }
        return false;
    }
    return false;
}

/*
* AALTO C++ media_player_8
* @function_type: incrementor function
* @desc: performs actual incrementation of iteration variable
* based on the output received from the playbackINdexController function
* @param: none
* @return: updated iterator index
*/
unsigned int playlistIterator::stepForward()
{
    if (playbackIndexController()) {
        //qDebug() << "incremention is allowed ";
        iterator_index += 1;
    } else {
//        qDebug() << "iterator index is on the border, incremetion is not allowed. Index returns to the beginning of playlist";
        iterator_index = 0;
    }

    return iterator_index;
}

/*
* AALTO C++ media_player_8
* @function_type: decrementor function
* @desc: performs actual decrementation of iteration variable
* based on the output received from the playbackINdexController function
* @param: none
* @return: updated iterator index
*/
unsigned int playlistIterator::stepBack()
{
    if (playbackIndexController()) {
        //qDebug() << "decremention is allowed ";
        iterator_index -= 1;
    } else {
//         qDebug() << "iterator index is on the border, decremention is not allowed. Index returns to the end of the playlist.";
        iterator_index = max_value;
    }
    return iterator_index;
}

