//
// Created by DisDev on 14.11.2015.
//

#ifndef STRUCTVALIDATOR_VALIDATOR_H
#define STRUCTVALIDATOR_VALIDATOR_H


#include <stdlib.h>
#include "../files/FileReader.h"
#include "ErrorHandler.h"
#include "../holders/KeyWordsArray.h"

#define INVALID_STRUCT_MESSAGE "������������ ���������� ���������. "
#define INVALID_NAME_MESSAGE "������������ ���������� ��������������. "

class StructDefineValidator {

    //static const char[][10] = {{}};

    FileReader*reader;
    ErrorHandler handler;
    ErrorHandler* hPointer;
    KeyWordsArray* keyWordsHolder;

    char* source;

    bool typeGlobalDefine;

    bool checkHeadDefine();
    bool checkBraketsAndLastSemicolon();
    bool readAndCheckFields();

    bool checkName(const char *name);
    bool checkType(const char *type);
public:

    StructDefineValidator(FileReader *reader, ErrorHandler *handler)
    {
        this->reader = reader;
        this->handler = *handler;
        hPointer = handler;
        source = nullptr;
        typeGlobalDefine = true;
        keyWordsHolder = new KeyWordsArray();
    }

    ~StructDefineValidator()
    {
        delete reader;
        delete hPointer;
        delete keyWordsHolder;
        free(source);
    }

    void valid();
};


#endif //STRUCTVALIDATOR_VALIDATOR_H
