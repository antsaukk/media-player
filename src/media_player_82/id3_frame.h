#ifndef ID3_FRAME_H
#define ID3_FRAME_H

#include <string>
#include <vector>


// A class to represent a single frame of an ID3-tag.
// A frame contains a header, specifying an ID; the size of the frame and some flags,
// and a value (the actual content of the frame)

class ID3_Frame
{
public:
    ID3_Frame(std::vector<char> header_, std::vector<char> value_);
    ID3_Frame(std::string& id, std::string& value_, int flags = 0);

    std::string getValue() const;
    std::string getID() const;
    std::vector<char> getHeader() const { return header; }
    int getFrameSize() const;
    int getFlags() const;
    int getHeaderLength() const { return headerLength; }

    void modifyValue(std::string& newValue);

private:
    static const int headerLength = 10;

    // Header of the frame
    std::vector<char> header;

    // Value of the frame
    std::vector<char> value;
};

#endif // ID3_FRAME_H
