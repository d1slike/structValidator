//
// Created by DisDev on 14.11.2015.
//

#include <iostream>
#include <stdio.h>
#include "ErrorHandler.h"

void ErrorHandler::operator<<(const char *message) {
    printf("ERROR: %s", message);
}
