#include "song.h"
#include <QMediaContent>
#include <sstream>
#include <iostream>

// Initializes the Song as QMediaContent object.
// Also initializes the ID3 tag, given a filename
Song::Song(const QUrl &url)
    : QMediaContent(url),
      id3Tag(new ID3_Tag(url.toString().toStdString()))
{

}

Song::~Song()
{
    //id3Tag->~ID3_Tag();
    //delete id3Tag;
}

/*
* AALTO C++ media_player_8
* @function_type:
* @desc:
* @param:
* @return:
*/
//Song::Song(const Song &song)
//{
//    QMediaContent(song.canonicalUrl());
//    id3Tag = song.id3Tag;
//}

//Song& Song::operator=(const Song &song)
//{
//    delete id3Tag;
//    QMediaContent(song.canonicalUrl());
//    id3Tag = song.id3Tag;
//    return *this;
//}

