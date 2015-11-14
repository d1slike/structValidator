//
// Created by DisDev on 14.11.2015.
//

#ifndef STRUCTVALIDATOR_VALIDATOR_H
#define STRUCTVALIDATOR_VALIDATOR_H


#include "../files/FileReader.h"
#include "ErrorHandler.h"

class Validator {
    FileReader* file;
    ErrorHandler handler;
    ErrorHandler* hPointer;

public:

    Validator(FileReader* reader, ErrorHandler* handler)
    {
        file = reader;
        this->handler = *handler;
        hPointer = handler;
    }

    ~Validator()
    {
        delete file;
        delete hPointer;
    }

    void valid();
};


#endif //STRUCTVALIDATOR_VALIDATOR_H
