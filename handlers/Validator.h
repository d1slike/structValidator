//
// Created by DisDev on 14.11.2015.
//

#ifndef STRUCTVALIDATOR_VALIDATOR_H
#define STRUCTVALIDATOR_VALIDATOR_H


#include <stdlib.h>
#include "../files/FileReader.h"
#include "ErrorHandler.h"
#include "../holders/KeyWordsArray.h"

class Validator {

    //static const char[][10] = {{}};

    FileReader*reader;
    ErrorHandler handler;
    ErrorHandler* hPointer;
    KeyWordsArray* keyWordsHolder;

    char* source;
    int lineInSource;

    bool checkHeadDefine();
    bool checkBraketsAndLastSemicolon();
    bool readAndCheckFields();

    bool checkName(char* name);
    bool checkName(char* name, int nameLentgh);


public:

    Validator(FileReader* reader, ErrorHandler* handler)
    {
        this->reader = reader;
        this->handler = *handler;
        hPointer = handler;
        source = nullptr;
        lineInSource = 0;
        keyWordsHolder = new KeyWordsArray();
    }

    ~Validator()
    {
        delete reader;
        delete hPointer;
        delete keyWordsHolder;
        free(source);
    }

    void valid();
};


#endif //STRUCTVALIDATOR_VALIDATOR_H
