#include "id3_frame.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

// A constructor to be used when reading the data from a file
ID3_Frame::ID3_Frame(std::vector<char> header_, std::vector<char> value_)
    : header(header_), value(value_)
{

}

// Helper function to get the frame size bytes from an int
std::vector<char> intToBytes_frame(int a)
{
    std::vector<char> res;
    for (int i = 0; i < 4; i++) {
        res.push_back((a >> (3-i)*8) & (0xff));
    }
    return res;
}

// A constructor to be used when creating a new frame. ID and value given as strings,
// flags as an int (default value 0). Parses the header to match the id, the value and the flags
ID3_Frame::ID3_Frame(std::string& id, std::string& value_, int flags)
    : value(value_.begin(), value_.end())
{
    std::vector<char> sizeBytes = intToBytes_frame(value_.length() + 1);
    for (int i = 0; i < 4; i++) header.push_back(id[i]);
    for (int i = 0; i < 4; i++) header.push_back(sizeBytes[i]);
    header.push_back((flags >> 8) & 0xff);
    header.push_back(flags & 0xff);

    value.insert(value.begin(), 0);

    for (auto c : header) {
        std::cout << (int) c << " ";
    }
    std::cout << std::endl;
}

// Returns the value of the frame, parsed into a string
std::string ID3_Frame::getValue() const
{
    std::string s(value.begin(), value.end());
    return s;
}

// Returns the ID of the frame (first 4 bytes of header)
std::string ID3_Frame::getID() const
{
    std::string s(header.begin(), header.begin() + 4);
    return s;
}

// Returns the flags of frame (last two bytes of header)
int ID3_Frame::getFlags() const
{
    return ((int) header[8] << 8 | (int) header[9]);
}

// Returns the size of the value of the frame, ie. the total length of the frame
// excluding the length of the header
int ID3_Frame::getFrameSize() const
{
    return value.size();
}

// Modifies the value of the frame. Updates the header to match the new value length as well
void ID3_Frame::modifyValue(std::string& newValue)
{
    value.clear();
    for (auto chr : newValue) {
        value.push_back(chr);
    }

    std::vector<char> newSizeBytes = intToBytes_frame(value.size() + 1);
    for (int i = 4; i < 8; i++) {
        header[i] = newSizeBytes[i-4];
    }
}



