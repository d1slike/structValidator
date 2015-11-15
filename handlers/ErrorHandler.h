//
// Created by DisDev on 14.11.2015.
//

#ifndef STRUCTVALIDATOR_ERRORHANDLER_H
#define STRUCTVALIDATOR_ERRORHANDLER_H

class ErrorStream {
public:
    ErrorStream operator<<(const char *message);
};

class ErrorHandler {
    ErrorStream stream;
public:

    ErrorHandler() {
        stream = ErrorStream();
    }

public:
    ErrorStream error();

    ErrorStream warn();
};


#endif //STRUCTVALIDATOR_ERRORHANDLER_H
