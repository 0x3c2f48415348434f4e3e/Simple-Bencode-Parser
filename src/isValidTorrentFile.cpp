#include"../include/readTorrentFile.cpp"

validTorrentFile::validTorrentFile(std::string &fileExtension): fileExtension(fileExtension){
    this->computeTorrentFile();
}

void validTorrentFile::computeTorrentFile(){
    while(moveablePointerToFileExtension <  this->getfileExtensionLength()){
        //check if we have a period (use ASCII, more safer, i think)
        if(fileExtension.at(moveablePointerToFileExtension) == 46){ //from the ASCII table 46 is . (period)
            lastPeriodCharacter = moveablePointerToFileExtension;
        }
        moveablePointerToFileExtension++;
    }

    //Now that we have the last period, check the extension
    
    return
}


int validTorrentFile::getfileExtensionLength(){
    return torrentFileExtension.size();
}