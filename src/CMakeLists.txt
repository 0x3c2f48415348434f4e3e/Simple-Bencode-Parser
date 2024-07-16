# specify minimu version for Cmake
cmake_minimum_required(VERSION, 3.22.1)

# specify project name
project(BencodeParser)

# Make output
add_executable(BencodeParser isValidTorrent.cpp readTorrentFile.cpp)