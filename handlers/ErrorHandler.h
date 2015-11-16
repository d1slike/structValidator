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
public:

    ErrorHandler() {
        stream = ErrorStream();
    }

    int calcLineNumber(const char *source, const char *startErrorPointer);

public:
    ErrorStream error();

    ErrorStream error(const char *source, const char *startErrorPointer);
    ErrorStream warn();
};


#endif //STRUCTVALIDATOR_ERRORHANDLER_H
