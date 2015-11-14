//
// Created by DisDev on 14.11.2015.
//

#include <iostream>
#include <stdio.h>
#include "ErrorHandler.h"

ErrorHandler ErrorHandler::operator<<(const char *message) {
    printf("ERROR: %s ", message);
    return *this;
}
