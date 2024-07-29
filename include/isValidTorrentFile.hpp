#ifndef VALIDTORRENTFILE
#define VALIDTORRENTFILE
#include"../common.hpp"

class validTorrentFile{
    private:
    std::string fileExtension;
    const std::string torrentFileExtension = ".torrent";
    int fileExtenstionLength;
    int moveablePointerToFileExtension = 0;
    int lastPeriodCharacter = 0;
    bool isValid = false;
    bool isValidTorrentFile();
    int getfileExtensionLength();

    public:
    //constructor
    validTorrentFile(std::string& fileExtension);
    bool computeTorrentFile(); //check if is torrent file
    //destructor
    ~validTorrentFile();
};
#endif //VALIDTORRENTFILE