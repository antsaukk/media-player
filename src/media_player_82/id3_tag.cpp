 #include "id3_tag.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>
#include <stdio.h>
#include <assert.h>
#include <QDebug>

ID3_Tag::ID3_Tag(std::string filename_) : header(headerLength)
{
    if (filename_.size() >= 20 && filename_.substr(0, 7) == "file://") {
        filename = filename_.substr(7, filename_.length());

#ifdef Q_OS_WIN
        filename = filename.substr(1, filename.length());
#endif

    } else {
        filename = filename_;
    }

    std::ifstream is;
    is.open(filename, std::ios::binary);
    if (!initHeader(is)) { qDebug() << "No ID3 tag found, filename: " << QString::fromStdString(filename); return; }

    initFrames(is);
    is.close();
}

ID3_Tag::~ID3_Tag()
{
    for (auto frame : frames) {
        delete frame;
    }
}


// Reads data from the stream is to the header. Assumes the stream is in the beginning of the file
bool ID3_Tag::initHeader(std::ifstream& is)
{
    is.read(&header[0], headerLength);
    if (header[0] == 'I' && header[1] == 'D' && header[2] == '3') return true;
    return false;
}

// Reads data from the stream to construct a new frame, and adds the new frame to the tag until all
// the frames are read. Assumes the stream is at the start of the frames, ie. the tag header is already read.
void ID3_Tag::initFrames(std::ifstream& is)
{
    int tagSize = getTagSize();
    int bytesRead = headerLength;
    char nextByte;
    is.read(&nextByte, 1);

    while (bytesRead < tagSize && (int) nextByte != 0) {
        is.seekg(-1, is.cur);

        ID3_Frame* frame = initFrame(is);
        bytesRead += frame->getHeaderLength() + frame->getFrameSize();
        frames.push_back(frame);

        is.read(&nextByte, 1);
    }
}

// A helper method to parse the size of a frame from 4 bytes of data
int getFrameSize(std::vector<char> sizeBytes)
{
    int res = 0;
    for (auto b : sizeBytes) {
        res = (res << 8) | b;
    }
    return res;
}

// Reads data from the stream and returns a new frame based on the data.
// Assumes the stream is at the start of a frame.
ID3_Frame* ID3_Tag::initFrame(std::ifstream& is)
{
    std::vector<char> frameHeader(headerLength);
    is.read(&frameHeader[0], headerLength);

    std::vector<char> sizeBytes(frameHeader.begin() + 4, frameHeader.begin() + 8);
    int frameSize = getFrameSize(sizeBytes);
    std::vector<char> frameValue(frameSize-1);
    is.ignore(1);
    is.read(&frameValue[0], frameSize-1);

    ID3_Frame* newFrame;
    newFrame = new ID3_Frame(frameHeader, frameValue);
    return newFrame;
}

// A helper method to get the size of the tag from the tag header.
// Note the format used in ID3v2 tags where the most significant bit of each is zeroed and ignored.
int ID3_Tag::getTagSize() const
{
    int res = 0;
    std::vector<char> sizeBytes(header.begin() + 6, header.end());
    for (auto b : sizeBytes) {
        res = (res << 7) | (int) b;
    }
    return res + headerLength;
}

// A helper method to get the tag size bytes from an int
std::vector<char> intToBytes_tag(int a) {
    std::vector<char> res;
    for (int i = 3; i >= 0; i--) {
        res.push_back((a >> i*7) & 0x7f);
    }
    return res;
}

// Returns the used size of the tag, ie. the total size - padding size
int ID3_Tag::getUsedSize() const
{
    int res = headerLength;
    for (auto frame : frames) {
        res += frame->getFrameSize() + frame->getHeaderLength();
    }
    return res;
}

// Returns the ID3v2 version of the tag, eg. "4.0" or "2.3"
std::string ID3_Tag::getVersion() const
{
    return std::to_string((int) header[3]) + "." + std::to_string((int) header[4]);
}

// Returns the flags in the tag header
int ID3_Tag::getFlags() const
{
    return (int) header[5];
}

// Returns a frame pointer with a given id
ID3_Frame* ID3_Tag::getFrame(std::string id) const
{
    for (auto frame : frames) {
        if (frame->getID() == id) {
            return frame;
        }
    }
    qDebug() << "ID3_Tag::getFrame : no frame with id" << QString::fromStdString(id) << "found";
    return nullptr;
}

// Returns the value of a frame with a given ID
std::string ID3_Tag::getFrameValue(std::string id) const
{
    for (auto frame : frames) {
        if (frame->getID() == id) {
            return frame->getValue();
        }
    }
    return "No value found";
}

// Updates the header of the tag to match a new tagsize
void ID3_Tag::setTagSize(int newSize)
{
    std::vector<char> newSizeBytes = intToBytes_tag(newSize);
    for (int i = 6; i < 10; i++) {
        header[i] = newSizeBytes[i-6];
    }
}

// Sets a new value for the frame with a given ID. Updates the value if the frame
// already exists, otherwise creates a new frame
void ID3_Tag::setValue(std::string& id, std::string& value)
{
    if (getTagSize() == headerLength) {
        qDebug() << "ID3_Tag::setValue: No ID3 tag was found, cannot edit metadata";
        return;
    }

    assert(id.length() == 4);

    for (auto frame : frames) {
        if (frame->getID() == id) {
            modifyValue(frame, value);
            return;
        }
    }

    ID3_Frame* newFrame = new ID3_Frame(id, value);
    frames.push_back(newFrame);

    int newBytesNeeded = newFrame->getHeaderLength() + value.length();
    int usedSize = getUsedSize();
    updateFile(newBytesNeeded, usedSize);
}

// Modifies the value of a given frame
void ID3_Tag::modifyValue(ID3_Frame* frame, std::string& newValue)
{
    int curValueLength = frame->getFrameSize();
    int usedSize = getUsedSize();
    frame->modifyValue(newValue);
    int newBytesNeeded = std::max(0, int(newValue.length() - curValueLength));

    updateFile(newBytesNeeded, usedSize);
}

// Updates the file of the tag. To be used after a change has been made to the tag.
// Parameters: how many new bytes are needed and how many bytes have been used before the change
// (ie. total size of the tag - padding)
void ID3_Tag::updateFile(int newBytesNeeded, int usedSize)
{
    int oldTagSize = getTagSize();
    int availableBytes = oldTagSize - usedSize;

    if (availableBytes < newBytesNeeded) {
        int newSize = 2 * oldTagSize;
        setTagSize(newSize - headerLength);
        rewriteFile(oldTagSize);
    } else {
        rewriteTag();
    }
}

// A helper method to get the size of a file in bytes
int getFileSize(const std::string &fileName)
{
    std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);
    if(!file.is_open()) return -1;
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

// Rewrites the tag in the file using the data in this object. To be used when there is
// enough space (padding) in the tag for the changes
void ID3_Tag::rewriteTag()
{
    std::fstream fs;
    fs.open(filename, std::ios::binary | std::ios::out | std::ios::in);
    if (!fs.good()) {
        qDebug() << "Error while opening file in function rewriteTag, filename: " <<
                    QString::fromStdString(filename);
        fs.close();
        return;
    }

    fs.write(&header[0], headerLength);
    for (auto frame : frames) {
        fs.write(&frame->getHeader()[0], frame->getHeaderLength());
        char zero = 0;
        fs.write(&zero, 1);
        fs.write(&frame->getValue()[0], frame->getFrameSize());
    }

    int pad = getTagSize() - getUsedSize();
    if (pad < 0) {
        qDebug() << "Error in rewriteTag: pad is negative (" << pad << ")";
        fs.close();
        return;
    }

    for (int i = 0; i < pad; i++) {
        char zero = 0;
        fs.write(&zero, 1);
    }

    fs.close();
}

// Rewrites the whole file. To be used when there's not enough space for changes in metadata
// Reads the actual mp3 data, writes the enlarged tag and writes back the mp3 data
void ID3_Tag::rewriteFile(int oldTagSize)
{
    std::fstream fs;
    fs.open(filename, std::ios::binary | std::ios::out | std::ios::in);
    if (!fs.good()) {
        qDebug() << "Error while opening file in function rewriteFile, filename: " <<
                    QString::fromStdString(filename);
        fs.close();
        return;
    }

    int fileSize = getFileSize(filename);
    int mp3DataSize = fileSize - oldTagSize;
    if (mp3DataSize <= 0) {
        qDebug() << "Error in rewriteFile: negative mp3DataSize (filesize: " <<
                    fileSize << ", oldTagSize: " << oldTagSize << ")";
        fs.close();
        return;
    }

    std::vector<char> mp3Data(mp3DataSize);
    fs.seekg(oldTagSize, std::ios::beg);
    fs.read(&mp3Data[0], mp3DataSize);
    fs.close();

    rewriteTag();

    fs.open(filename, std::ios::binary | std::ios::out | std::ios::in);
    if (!fs.good()) {
        qDebug() << "Error while opening file in function rewriteFile, filename: " <<
                    QString::fromStdString(filename);
        fs.close();
        return;
    }

    fs.seekg(getTagSize(), std::ios::beg);
    fs.write(&mp3Data[0], mp3DataSize);
    fs.close();
}


