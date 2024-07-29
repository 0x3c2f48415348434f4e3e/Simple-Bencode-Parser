#include"../include/logger.hpp"

Logger::Logger(){}

void Logger::methodEntry(std::string& methodName,void (*methodEntryCallBack)(std::string& methodName)){
    (*methodEntryCallBack)(methodName);
}

Logger::~Logger(){}