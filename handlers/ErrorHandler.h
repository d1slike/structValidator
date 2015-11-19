//
// Created by DisDev on 14.11.2015.
//

#ifndef STRUCTVALIDATOR_ERRORHANDLER_H
#define STRUCTVALIDATOR_ERRORHANDLER_H

#define ENDL '\n'

class ErrorStream {
public:
    ErrorStream operator<<(const char *message);

    ErrorStream operator<<(const char message);
};

class ErrorHandler {
    ErrorStream stream;
    char *startSource;
public:

    ErrorHandler() {
        stream = ErrorStream();
        startSource = nullptr;
    }

    int calcLineNumber(const char *startErrorPointer);

public:
    ErrorStream error();

    void setStartSourcePointer(char *source);

    ErrorStream error(const char *startErrorPointer);
    ErrorStream warn();
};


#endif //STRUCTVALIDATOR_ERRORHANDLER_H
