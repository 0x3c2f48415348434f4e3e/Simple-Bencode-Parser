#ifndef VALIDTORRENTFILE
#define VALIDTORRENTFILE
#include"../common.hpp"

class validTorrentFile(){
    private:
    const std::string fileExtension;
    const std::string torrentFileExtension = ".torrent";
    int fileExtenstionLength;
    int moveablePointerToFileExtension = 0;
    int lastPeriodCharacter = 0;
    bool isValid = false;

    public:
    //constructor
    validTorrentFile(std::string &fileExtension);
    void computeTorrentFile(); //check if is torrent file
    bool isValidTorrentFile();
    int getfileExtensionLength();

    //destructor
    ~validTorrentFile();
}
#endif //VALIDTORRENTFILE