//
// Created by Dislike on 15.11.2015.
//

#include "KeyWordsArray.h"


KeyWordsArray::KeyWordsArray() {
    array = new char *[KEY_WORDS_COUNT];
    for (int i = 0; i < KEY_WORDS_COUNT; i++)
        array[i] = new char[17];
    FileReader reader("keywords.txt");
    if (!reader.isReady()) {
        printf("?? ?????? ???? ? ????????? ???????. ????????? ?????????.");
        exit(-1);
    }
    char *full = reader.readFull();
    reader.close();
    int i, j;
    i = j = 0;
    while (*full) {
        if (*full == '\n') {
            array[i][j] = '\0';
            i++;
            j = 0;
            full++;
            continue;
        }
        array[i][j++] = *full++;
    }
    typeArray = new char *[TYPES_COUNT];
    for (int i = 0; i < TYPES_COUNT; i++)
        typeArray[i] = new char[10];
    i = 0;
    strcpy(typeArray[i++], "int");
    strcpy(typeArray[i++], "long");
    strcpy(typeArray[i++], "double");
    strcpy(typeArray[i++], "short");
    strcpy(typeArray[i++], "float");
    strcpy(typeArray[i++], "bool");


}

char *KeyWordsArray::getWord(int pos) {
    if (pos < 0 || pos >= KEY_WORDS_COUNT)
        return nullptr;
    return array[pos];
}

KeyWordsArray::~KeyWordsArray() {
    for (int i = 0; i < KEY_WORDS_COUNT; i++)
        delete[] array[i];
    for (int i = 0; i < TYPES_COUNT; i++)
        delete[] typeArray[i];
    delete[] array;
    delete[] typeArray;
}

char **KeyWordsArray::getArrayOfTypes() {
    return typeArray;
}
