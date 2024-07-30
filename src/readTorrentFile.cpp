#include"../include/readTorrentFile.hpp"
#include"../include/isValidTorrentFile.hpp"


readTorrentFile::readTorrentFile(std::string &fileName): fileName(fileName){
    this->Head = nullptr;
    this->Tail = nullptr;
    //check if file is a valid torrennt file
    validTorrentFile validTorrent(this->fileName);
    if(validTorrent.computeTorrentFile()){
        std::cout<<"Given File is a torrent file"<<std::endl;
    }else{
        std::cout<<"Given File is Not a torrent file"<<std::endl;
        exit(-1); //fix this later. Not necesary
    }

    this->innerProcess();
}

void readTorrentFile::innerProcess(){
    //set exception mask to trigger an exception for failbit and badbit
    this->TorrentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    //exception handling
    try{
        this->TorrentFile.open(this->fileName);
        //Get the number of lines within the file,
        //move file pointer to the end of the file
        this->TorrentFile.seekg(0,std::ios::end);
        //get current position
        std::streampos fileSize = this->TorrentFile.tellg();
        this->fileSize = fileSize;
        this->TorrentFile.seekg(0,std::ios::beg);
        std::cout<<"File size is: "<<fileSize<<std::endl;
    }catch(const std::ios_base::failure& e){
        //catch thr exception thrown
        //use the custom logger here
        std::cout<<"An Error occured: Tesst "<<std::endl;
        exit(-1);

    }
    unsigned char* buffer = new unsigned char[this->fileSize + 1];
    GLOBAL_POINTER_buffer = buffer;
    if (buffer == nullptr) {
        // Use custom log here
        std::cout << "Memory could not be allocated" << std::endl;
        exit(-1);
    }
    //Here what we will do is read the file using some C++ stuff, then transfer the content of the string to a cahr so we can work with it in a low level
    std::string fileContent;
    std::vector<std::string> lines;
    std::string combinedLines;

    memset(buffer, 0,sizeof(char)*(this->fileSize+1));

    //check if file is actually opened
    if(!(this->TorrentFile.is_open())){
        std::cerr << "Error opening the file!" << std::endl;
        exit(-1);
    }
    while(!(this->TorrentFile.eof())){
        std::getline(this->TorrentFile,fileContent);
        lines.push_back(fileContent);
    }
    std::cout<<"Done"<<std::endl;
    std::ostringstream oss;

    for(const auto& line : lines){
        oss << line << '\n';
    }
    combinedLines = oss.str();
    //std::cout<<combinedLines.c_str()<<std::endl;
    //do some inner processing because the way that C/C++ stores processes data is weird
    unsigned char *tempFileContent = (unsigned char *)  new unsigned char[sizeof(char)*this->fileSize];
    if (tempFileContent == nullptr) {
        // Use custom log here
        std::cout << "Memory could not be allocated" << std::endl;
        exit(-1);
    }

    lint_16 counter = 0;
    for(; counter<fileSize; counter++){
        if(reinterpret_cast<unsigned char*>(const_cast<char*>(combinedLines.c_str()))[counter] >= 32 && reinterpret_cast<unsigned char*>(const_cast<char*>(combinedLines.c_str()))[counter] <= 126){
            //replace with 0
            tempFileContent[counter] = reinterpret_cast<unsigned char*>(const_cast<char*>(combinedLines.c_str()))[counter];
        }
        else{
            tempFileContent[counter] = '0'; //replace such character with that
        }
    }

    this->lexer(tempFileContent);
    this->readBencode(this->Head);

}

lint_16 readTorrentFile::stringToInteger(unsigned char* string){
    lint_16 res = 0;
    int i = 0;
    for(;string[i] !='\0'; i++){
        res = (res * 10) + (string[i] - '0');
    }
    return res;
}


lint_16 readTorrentFile::lexer(const unsigned char *stream) {
    //std::cout<<stream<<std::endl;
    // using 2 pointers
    lint_16 pointer = 0;
    lint_16 pointer2 = 0;

    unsigned char *lexerResult = new unsigned char[this->BUFFER];
    if (lexerResult == nullptr) {
        std::cout << "Unable to allocate memory" << std::endl;
        exit(-1);
    }

    bencodeParser* element = new bencodeParser; //creates space in memory
    if (element == nullptr) {
        std::cout << "Unable To allocate memory" << std::endl;
        exit(-1);
    }
    element->next = nullptr;

    if (stream[pointer] == BencoderValues.INTEGER) {
        element->dataType = "Integer";
        pointer++; // skip the 'i'
        while (stream[pointer] != 'e') {
            lint_16 currentBufferSize = this->BUFFER;
            if (pointer2 >= this->BUFFER) {
                currentBufferSize += this->BUFFER;
                lexerResult = (unsigned char *) realloc(lexerResult, currentBufferSize);
                if (lexerResult == nullptr) {
                    std::cout << "Memory Allocation failed" << std::endl;
                    exit(-1);
                }
            }
            lexerResult[pointer2++] = stream[pointer++];
        }
        lexerResult[pointer2] = '\0';
        element->value.integerValue = this->stringToInteger(lexerResult);
        std::cout<<element->value.integerValue<<std::endl;
        pointer++; // skip 'e'
    } else if (stream[pointer] == BencoderValues.LIST) {
        element->dataType = "List";
        pointer++; // skip 'l'
        while (stream[pointer] != 'e') {
            pointer += this->lexer(stream + pointer);
        }
        pointer++; // skip 'e'
    } else if (stream[pointer] == BencoderValues.DICTIONARY) {
        element->dataType = "Dictionary";
        pointer++; // skip 'd'
        while (stream[pointer] != 'e') {
            pointer += this->lexer(stream + pointer);
        }
        pointer++; // skip 'e'
    } else {
        element->dataType = "String";
        unsigned char num[1000] = {0};
        int tempPoint = 0;
        while (stream[pointer] != ':') {
            num[tempPoint++] = stream[pointer++];
        }
        num[tempPoint] = '\0';
        int lengthOfString = stringToInteger(num);
        pointer++; // skip ':'
        element->value.stringValue = new unsigned char[lengthOfString + 1];
        if (element->value.stringValue == nullptr) {
            std::cout << "Unable to allocate memory" << std::endl;
            exit(-1);
        }
        memcpy(element->value.stringValue, &stream[pointer], lengthOfString);
        element->value.stringValue[lengthOfString] = '\0';
        std::cout<<element->value.stringValue<<std::endl;
        pointer += lengthOfString;
    }

    if (this->Head == nullptr) {
        this->Head = element;
        this->Tail = element;
    } else {
        this->Tail->next = element;
        this->Tail = element;
    }
    return pointer;
}


void readTorrentFile::readBencode(bencodeParser *Head){
	while(Head){
		if(compare(Head->dataType) == 1){
			std::cout<<Head->value.stringValue<<std::endl;
		}
		else if(compare(Head->dataType) == 2){
			std::cout<<Head->value.integerValue<<std::endl;
		}
		else if(compare(Head->dataType) == 3 || compare(Head->dataType) == 3){
            this->readBencode(Head->value.List_Dictionary);
		}
        else{
            std::cout<<"Unable to find"<<std::endl;
        }
		Head = Head->next;
	}
    return;
}

int readTorrentFile::compare(std::string string){

	
	// * Will return:
	// * 1 for string
	// * 2 for integer
	// * 3 for List and dictionary
	// *
    
	if(string == "String") return 1;
	if(string == "Integer") return 2;
	if((string == "List") || (string == "Dictionary")) return 3;
    return -1;
}

readTorrentFile::~readTorrentFile(){
    //free resources, and close files
    this->TorrentFile.close();
    //free all heap memory
    //delete ((unsigned char *)GLOBAL_POINTER_buffer);
    //delete ((bencodeParser *)GLOBAL_POINTER_element);
    //delete ((unsigned char *)GLOBAL_POINTER_lexerResult);
    //delete ((unsigned char *)GLOBAL_POINTER_value_stringValue);
}