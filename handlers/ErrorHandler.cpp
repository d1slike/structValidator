//
// Created by DisDev on 14.11.2015.
//

#include <stdio.h>
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

ErrorStream ErrorHandler::error(const char *source, const char *startErrorPointer) {
    printf("ÎØÈÁÊÀ: Ñòðîêà(%d): ", calcLineNumber(source, startErrorPointer) + 1);
    return stream;
}

int ErrorHandler::calcLineNumber(const char *source, const char *startErrorPointer) {
    int endlCount = 0;
    while (source != startErrorPointer)
        if (*(startErrorPointer--) == '\n')
            endlCount++;
    return endlCount;
}

ErrorStream ErrorStream::operator<<(const char message) {
    printf("%c", message);
    return *this;
}
