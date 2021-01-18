#include "tester.h"
#include <iostream>

typedef int (Tester::* Function)();

Tester::Tester(media_player* m_)
    : m(m_)
{
    add_test(&Tester::metadata_tests, "metadata");
    add_test(&Tester::playlist_tests, "playlist");
}

void Tester::add_test(Function f, QString name)
{
    test_functions.push_back(std::make_pair(f, name));
}

int Tester::run_tests()
{
    qDebug() << "\nBEGIN TESTS\n";

    int failures = 0;
    for (auto function : test_functions) {
        qDebug() << "BEGIN TESTING " << function.second.toUpper() << " FUNCTIONS\n";
        int new_failures = (*this.*(function.first))();
        qDebug() << "\nFINISHED TESTING " << function.second.toUpper() << " FUNCTIONS";
        qDebug() << "FAILURES: " << new_failures << "\n";
        failures += new_failures;
    }
    qDebug() << "FINISHED ALL TESTS\nTOTAL FAILURES: " << failures << "\n";
    return failures;
}

template <class T>
int should_be(std::string function_name, T a, T b)
{
    qDebug() << "Testing " << QString::fromStdString(function_name) << "...";
    if (a != b) { qDebug() << "FAILURE: " << a << " should be " << b; return 1; }
    return 0;
}

int Tester::metadata_tests()
{
    if (m->getPlaylist()->getLength() == 0) {
        qDebug() << "Metadata tests require a song in the /Music directory"
                    " (relative to the application directory)";
        return 0;
    }

    int failures = 0;

    Song song = m->getPlaylist()->getPlayList()[0];

    // setSongName

    std::string oldSongName = song.getID3Tag().getSongName();
    std::string testName = "testName";
    song.getID3Tag().setSongName(testName);

    ID3_Frame* frame = song.getID3Tag().getFrame("TIT2");
    if (frame != nullptr) failures += should_be("setSongName", frame->getFrameSize(), 8);
    failures += should_be("setSongName", QString::fromStdString(song.getID3Tag().getSongName()), QString::fromStdString(testName));
    song.getID3Tag().setSongName(oldSongName);

    return failures;
}

int Tester::playlist_tests()
{
    int playlistLength = m->getPlaylist()->getLength();

    if (playlistLength < 2) {
        qDebug() << "Playlist tests require at least two songs in the /Music directory"
                    " (relative to the application directory)";
        return 0;
    }

    int failures = 0;

    auto oldPos = m->getPlaylist()->getPlaybackControl().getPosition();
    m->getPlaylist()->next();
    auto newPos = m->getPlaylist()->getPlaybackControl().getPosition();
    failures += should_be("playback_iterator.position", oldPos + 1, newPos);

    m->getPlaylist()->back();
    newPos = m->getPlaylist()->getPlaybackControl().getPosition();
    failures += should_be("playback_iterator.position", oldPos, newPos);

    m->getPlaylist()->clearPlaylist();
    int newLength = m->getPlaylist()->getLength();
    should_be("clearPlaylist", newLength, 0);

    m->loadDefaultMP3Library();
    newLength = m->getPlaylist()->getLength();
    should_be("loadDefaultLibrary", newLength, playlistLength);

    int playlistMaxIndex = m->getPlaylist()->getPlaybackControl().getMaxPositionIndex();
    should_be("playback_iterator max index", playlistMaxIndex + 1, playlistLength);

    return failures;
}
