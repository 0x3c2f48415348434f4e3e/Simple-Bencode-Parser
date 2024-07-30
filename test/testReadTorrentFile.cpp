#include<iostream>
#include"../include/readTorrentFile.hpp"

int main(){
    //test\ubuntu-24.04-live-server-amd64.iso.torrent
    //std::string path = "./ubuntu-24.04-live-server-amd64.iso.torrent";
    std::string path = "./test.torrent";
    readTorrentFile torrentFile(path);
}