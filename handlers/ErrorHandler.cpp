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
    printf("ОШИБКА: ");
    return stream;
}

ErrorStream ErrorHandler::warn() {
    printf("ПРЕДУПРЕЖДЕНИ: ");
    return stream;
}
