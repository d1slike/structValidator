//
// Created by Dislike on 15.11.2015.
//

#ifndef STRUCTVALIDATOR_STRINGVECTOR_H
#define STRUCTVALIDATOR_STRINGVECTOR_H


class SimpleStringVector {
    char **array;
    int size;

public:

    SimpleStringVector();

    ~SimpleStringVector();

    void add(const char *source);

    bool contains(const char *str);
};


#endif //STRUCTVALIDATOR_STRINGVECTOR_H
