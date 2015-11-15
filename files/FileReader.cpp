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
    if (source != nullptr)
        fclose(source);
    source = nullptr;
}

char *FileReader::readFull() {
    char *full = (char *) malloc(CHAR_SIZE * 10);
    int count = 0;
    int i = 0;
    while (!isOnEOF()) {
        full[count++] = readNextChar();
        i++;
        if (i == 10) {
            full = (char *) realloc(full, ((count + 10) * CHAR_SIZE));
            if (full == nullptr) {
                printf("��������� ������, ���������� ���������.\n");
                exit(-1);
            }
            /*if(tmp != full)
            {
                free(full);
                full = tmp;
            }*/
            i = 0;
        }
    }

    return full;
}

char FileReader::readNextChar() {
    if (!isReady())
        return EOF;
    lastReaded = fgetc(source);
    if (isOnEOF())
        return '\0';
    return lastReaded;
}

bool FileReader::isOnEOF() {
    return lastReaded == EOF;
}



