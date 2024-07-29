#include"../include/isValidTorrentFile.hpp"

validTorrentFile::validTorrentFile(std::string& fileExtension) : fileExtension(fileExtension){
    //check thats given file is not empty
    if(fileExtension.size() == 0){
        std::cout<<"Input file extension can not be empty";
        exit(-1);
    }
}

bool validTorrentFile::computeTorrentFile(){
    while(this->moveablePointerToFileExtension < this->fileExtension.size()){//this->getfileExtensionLength()){
        //check if we have a period (use ASCII, more safer, i think)
        if(this->fileExtension.at(this->moveablePointerToFileExtension) == '.'){ //from the ASCII table 46 is . (period)
            this->lastPeriodCharacter = this->moveablePointerToFileExtension;
        }
        this->moveablePointerToFileExtension++;
    }

    //Now that we have the last period, check the extension
    std::string localFileExtension = this->fileExtension.substr(this->lastPeriodCharacter);
    if(localFileExtension == this->torrentFileExtension){
        //std::cout<<"Given File is a torrent file"<<std::endl;
        this->isValid = true;
    }
    
    return this->isValidTorrentFile();
}

int validTorrentFile::getfileExtensionLength(){
    return this->torrentFileExtension.size();
}

bool validTorrentFile::isValidTorrentFile(){
    return this->isValid;
}

validTorrentFile::~validTorrentFile(){
    std::cout<<"Process finished"<<std::endl;
}
