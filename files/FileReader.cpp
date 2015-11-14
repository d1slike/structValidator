//
// Created by DisDev on 14.11.2015.
//

#include <stdlib.h>
#include <iostream>
#include "FileReader.h"

bool FileReader::isReady() {
    return source != nullptr;
}

void FileReader::close() {
    fclose(source);
    source = nullptr;
}

char *FileReader::readFull() {
    char* full = (char*) malloc(CHAR_SIZE * 10);
    char c;
    int count = 0;
    int i = 0;
    while(!isOnEOF())
    {
        full[count++] = readNextChar();
        i++;
        if(i == 10)
        {
            full = (char *) realloc(full, ((count + 10) * CHAR_SIZE));
            if(full == nullptr)
            {
                printf("Нехватака памяти, завершение программы.\n");
                exit(-1);
            }
            i = 0;
        }
    }
}

char FileReader::readNextChar() {
    if(!isReady())
        return 0;
    lastReaded = fgetc(source);
    if(isOnEOF())
        return '\0';
    return lastReaded;
}

bool FileReader::isOnEOF() {
    return lastReaded == EOF;
}
