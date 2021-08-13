#include "song.h"
#include <QMediaContent>
#include <sstream>
#include <iostream>

/*
* AALTO C++ media_player_8
* @function_type:
* @desc: Initializes the Song as QMediaContent object, also initializes the ID3 tag, given a filename
* @param:
* @return:
*/
Song::Song(const QUrl &url)
    : QMediaContent(url),
      id3Tag(new ID3_Tag(url.toString().toStdString()))
{

}

Song::~Song() {}

