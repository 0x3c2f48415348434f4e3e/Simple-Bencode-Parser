#ifndef READTORRENTFILE
#define READTORRENTFILE

#include "../common.hpp"
#include <string>
#include <fstream>

// Full definition of the struct
typedef struct B {
    std::string dataType;
    union {
        lint_16 integerValue;
        unsigned char* stringValue;
        bencodeParser* List_Dictionary; // Using forward declaration here
    } value;
    bencodeParser* next; // Using forward declaration here
} bencodeParser;

// Forward declaration within the class
class readTorrentFile {

private:
    std::string fileName;
    lint_16 fileSize;
    std::fstream TorrentFile;
    void innerProcess();
    lint_16 lexer(const unsigned char *stream);
    const int BUFFER = 1024;
    lint_16 stringToInteger(unsigned char* string);
    void readBencode(bencodeParser *Head);
    int compare(std::string string);
    bencodeParser* Head;
    bencodeParser* Tail;

    BENCODEVALUES BencoderValues;

private:
    void* GLOBAL_POINTER_buffer = nullptr;
    void* GLOBAL_POINTER_lexerResult = nullptr;
    void* GLOBAL_POINTER_element = nullptr;
    void* GLOBAL_POINTER_value_stringValue = nullptr;

public:
    readTorrentFile(std::string& fileName);
    ~readTorrentFile();
};

#endif // READTORRENTFILE




/*#ifndef READTORRENTFILE
#define READTORRENTFILE
#include"../common.hpp"

class readTorrentFile{
    private:
    std::string fileName;
    lint_16 fileSize;
    std::fstream TorrentFile;
    void innerProcess();
    lint_16 lexer(const unsigned char *stream);
    const int BUFFER = 1024;
    lint_16 stringToInteger(unsigned char* string);

public:
    typedef struct B bencodeParser;
    //have our struct here
    typedef struct B{
        std::string dataType;
        union{
            lint_16 integerValue;
            unsigned char* stringValue;
            bencodeParser* List_Dictionary;
        }value;
        bencodeParser* next;
    }bencodeParser;
private:
    BENCODEVALUES BencoderValues;
    //bencodeParser parser;
public:
    bencodeParser *Head = nullptr;
    bencodeParser *Tail = nullptr;
private:
    void* GLOBAL_POINTER_buffer = nullptr;
    void* GLOBAL_POINTER_lexerResult = nullptr;
    void* GLOBAL_POINTER_element = nullptr;
    void* GLOBAL_POINTER_value_stringValue = nullptr;

public:
    readTorrentFile(std::string &fileName);
    ~readTorrentFile();
};

#endif //READTORRENTFILE
*/