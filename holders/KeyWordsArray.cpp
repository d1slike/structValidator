//
// Created by Dislike on 15.11.2015.
//

#include "KeyWordsArray.h"


KeyWordsArray::KeyWordsArray() {
    array = new char*[KEY_WORDS_COUNT];
    for(int i = 0; i < KEY_WORDS_COUNT; i++)
        array[i] = new char[16];
    FileReader reader("keywords.txt");
    if(!reader.isReady())
    {
        printf("Не найден файл с ключевыми словами. Программа завершена.");
        exit(-1);
    }
    char* full = reader.readFull();
    reader.close();
    int i,j;
    i = j = 0;
    while(*full)
    {
        if(*full == '\n') {
            i++;
            j = 0;
            continue;
        }
        array[i][j++] = *full++;
    }

}

char *KeyWordsArray::getWord(int pos) {
    if(pos < 0 || pos >= KEY_WORDS_COUNT)
        return nullptr;
    return array[pos];
}

KeyWordsArray::~KeyWordsArray() {
    for(int i = 0; i < KEY_WORDS_COUNT; i++)
        delete [] array[i];
    delete [] array;
}
