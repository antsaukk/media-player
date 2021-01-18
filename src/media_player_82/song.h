#ifndef SONG_H
#define SONG_H

#include <QMediaContent>
#include "id3_tag.h"


// A Song object to be used in a QMediaPlaylist. Uses the QMediaContent functionality,
// with added support to handle the metadata of the file

class Song : public QMediaContent
{
public:
    Song(const QUrl &url);

    ~Song();

//    Song(const Song &song);

//    Song& operator= (const Song &song);

    ID3_Tag& getID3Tag() { return *id3Tag; }

private:
    // A metadata container
    ID3_Tag* id3Tag;

};

#endif // SONG_H
