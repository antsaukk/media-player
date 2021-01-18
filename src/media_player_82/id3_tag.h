#ifndef ID3_TAG_H
#define ID3_TAG_H

#include <string>
#include <vector>
#include "id3_frame.h"

// ID3v2 metadata container. An ID3 tag consists of a header, specifying the version of ID3 used;
// the length of the tag and some flags, followed by some amount of frames that contain the actual metadata
// eg. the song name and the artist

class ID3_Tag
{
public:
    ID3_Tag(std::string filename_);

    ~ID3_Tag();

    bool initHeader(std::ifstream& is);
    ID3_Frame* initFrame(std::ifstream& is);
    void initFrames(std::ifstream& is);

    std::string getFilename() const { return filename; }
    std::string getVersion() const;
    int getFlags() const;
    int getTagSize() const;
    int getUsedSize() const;

    ID3_Frame* getFrame(std::string id) const;

    std::string getFrameValue(std::string id) const;

    // Returns the value of the song title frame
    std::string getSongName() const { return getFrameValue("TIT2"); }

    // Returns the value of the artist frame
    std::string getArtist() const { return getFrameValue("TPE1"); }

    // Returns the value of the album frame
    std::string getAlbum() const { return getFrameValue("TALB"); }

    // Sets the value of song title frame. Adds the frame if it doesn't exists
    void setSongName(std::string& value) { std::string id = "TIT2"; setValue(id, value); }

    // Sets the value of artist frame. Adds the frame if it doesn't exists
    void setArtist(std::string& value) { std::string id = "TPE1"; setValue(id, value); }

    // Sets the value of album frame. Adds the frame if it doesn't exists
    void setAlbum(std::string& value) { std::string id = "TALB"; setValue(id, value); }

    void setTagSize(int newSize);

    void setValue(std::string& id, std::string& value);

    void modifyValue(ID3_Frame* frame, std::string& newValue);

    void rewriteTag();

    void rewriteFile(int oldTagSize);

private:
    std::string filename;
    static const int headerLength = 10;

    // A header (first 10 bytes of data) of the tag
    std::vector<char> header;

    // A container for the frames
    std::vector<ID3_Frame*> frames;

    void updateFile(int newBytesNeeded, int usedSize);
};

#endif // ID3_TAG_H
