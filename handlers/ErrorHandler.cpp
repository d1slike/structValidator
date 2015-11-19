//
// Created by DisDev on 14.11.2015.
//

#include <stdio.h>
#include <string.h>
#include "ErrorHandler.h"

ErrorStream ErrorStream::operator<<(const char *message) {
    printf("%s", message);
    return *this;
}

ErrorStream ErrorHandler::error() {
    printf("ÎØÈÁÊÀ: ");
    return stream;
}

ErrorStream ErrorHandler::warn() {
    printf("ÏÐÅÄÓÏÐÅÆÄÅÍÈÅ: ");
    return stream;
}

ErrorStream ErrorHandler::error(const char *startErrorPointer) {
    printf("ÎØÈÁÊÀ: Ñòðîêà(%d): ", calcLineNumber(startErrorPointer) + 1);
    return stream;
}

int ErrorHandler::calcLineNumber(const char *startErrorPointer) {
    int endlCount = 0;
    char *start = startSource;
    if (start == nullptr)
        return -2;
    char *end = strstr(start, startErrorPointer);
    while (start < end)
        if (*(start++) == '\n')
            endlCount++;
    return endlCount;
}

ErrorStream ErrorStream::operator<<(const char message) {
    printf("%c", message);
    return *this;
}

void ErrorHandler::setStartSourcePointer(char *source) {
    startSource = source;
}
