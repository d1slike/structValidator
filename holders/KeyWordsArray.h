//
// Created by Dislike on 15.11.2015.
//

#ifndef STRUCTVALIDATOR_KEYWORDSARRAY_H
#define STRUCTVALIDATOR_KEYWORDSARRAY_H

#define KEY_WORDS_COUNT 84

#include <stdlib.h>
#include <string.h>
#include "../files/FileReader.h"

class KeyWordsArray {

    char** array;

public:
    KeyWordsArray();
    ~KeyWordsArray();
    char * getWord(int pos);

};


#endif //STRUCTVALIDATOR_KEYWORDSARRAY_H
