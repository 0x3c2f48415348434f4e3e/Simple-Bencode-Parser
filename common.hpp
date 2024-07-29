#ifndef __COMMON
#define __COMMON
#include<iostream>
#include<fstream>
#include <cstring>
#include<vector>
#include <sstream>
//override the assert
#define NDEBUG
#define assert(expression) {if(!(expression)) std::cout<<"ERROR"<<std::endl; exit(-1);}
typedef unsigned long int lint_16;
//typedef enum {BYTE_STRING = 0x20, INTEGER = 0x69, LIST = 0x6C, DICTIONARY = 0x64};
typedef struct B bencodeParser;
typedef struct{
    char BYTE_STRING = 0x20;
    char INTEGER = 'i';//0x69;
    char LIST = 'l';//0x6C;
    char DICTIONARY = 'd';//0x64;
}BENCODEVALUES;
/*
String ->
Integer ->
List ->
Dictionary
*/

#endif //__COMMON