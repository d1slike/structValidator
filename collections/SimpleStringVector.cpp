//
// Created by Dislike on 15.11.2015.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SimpleStringVector.h"

void SimpleStringVector::add(const char *source) {
    array = (char **) realloc(array, ++size * sizeof(char **));
    if (array == nullptr) {
        printf("Ошибка выделения памяти.");
        exit(-1);
    }
    array[size - 1] = (char *) malloc((strlen(source) + 1) * sizeof(char));
    if (array[size - 1] == nullptr) {
        if (array == nullptr) {
            printf("Ошибка выделения памяти.");
            exit(-1);
        }
    }
    memcpy(array[size - 1], source, (strlen(source) + 1) * sizeof(char));

}

bool SimpleStringVector::contains(const char *str) {
    for (int i = 0; i < size; i++)
        if (!strcmp(array[i], str))
            return true;
    return false;
}

SimpleStringVector::~SimpleStringVector() {
    for (int i = 0; i < size; i++)
        free(array[i]);
    free(array);
}

SimpleStringVector::SimpleStringVector() {
    array = nullptr;
    size = 0;
}
