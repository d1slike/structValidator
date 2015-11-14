//
// Created by DisDev on 14.11.2015.
//

#ifndef STRUCTVALIDATOR_FILE_H
#define STRUCTVALIDATOR_FILE_H


#include <stdio.h>


class FileReader {

    static const long CHAR_SIZE = sizeof(char);

    FILE* source;
    char lastReaded;

    char readNextChar();
    bool isOnEOF();
public:
    FileReader(const char* name)
    {
        source = fopen(name, "r");
    }
    ~FileReader()
    {
        fclose(source);
    }
    bool isReady();
    char* readFull();
    void close();

};


#endif //STRUCTVALIDATOR_FILE_H
