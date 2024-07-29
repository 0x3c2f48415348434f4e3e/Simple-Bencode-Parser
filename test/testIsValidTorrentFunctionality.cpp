#include<iostream>
#include"../include/isValidTorrentFile.hpp"
int main(){
validTorrentFile instance("ubuntu-24.04-live-server-amd64.iso.torrent");
if(instance.computeTorrentFile()){
    std::cout<<"Given File is a torrent file"<<std::endl;
}else{
    std::cout<<"Given File is Not a torrent file"<<std::endl;
}
}