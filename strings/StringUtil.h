//
// Created by Dislike on 15.11.2015.
//

#ifndef STRUCTVALIDATOR_STRINGUTIL_H
#define STRUCTVALIDATOR_STRINGUTIL_H

#include <string.h>

namespace string
{
    bool startWith(const char* source, const char* str)
    {
        int strLen = strlen(str);
        int sourceLen = strlen(source);
        if(strLen > sourceLen)
            return false;
        for(register int i = 0; i < strLen; i++)
            if(*(source + i) != *(str + i))
                return false;
        return true;
    }
}
#endif //STRUCTVALIDATOR_STRINGUTIL_H
