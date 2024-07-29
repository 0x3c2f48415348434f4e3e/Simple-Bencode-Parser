# specify minimu version for Cmake
cmake_minimum_required(VERSION, 3.22.1)

# specify project name
project(BencodeParser)

#Include the root directory of project
include_directory("${PROJECT_SOURCE_DIR}")

# Make output
add_executable(BencodeParser ${PROJECT_SOURCE_DIR}/isValidTorrent.cpp ${PROJECT_SOURCE_DIR}/readTorrentFile.cpp)