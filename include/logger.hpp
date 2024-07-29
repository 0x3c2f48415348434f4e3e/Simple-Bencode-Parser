#ifndef __DEBUGLOG
#define __DEBUGLOG
#include"common.h"

//logger utility class

//callback for methodEntry
#define METHODENTRY(name) {std::cout<<name<<std::endl}
class Logger{
    private:
    public:
        Logger();
        void methodEntry(std::string&methodName,void (*methodEntryCallBack)(std::string& methodName));
        ~Logger()
}

#endif //__DEBUGLOG