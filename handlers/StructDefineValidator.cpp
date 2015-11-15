//
// Created by DisDev on 14.11.2015.
//

#include <string.h>
#include <ctype.h>
#include "StructDefineValidator.h"
#include "../collections/SimpleStringVector.h"

void StructDefineValidator::valid() {
    if (!reader->isReady()) {
        handler.error() << "Ошибка чтения файла! Файл отсутствует или пуст.\n";
        exit(-1);
    }
    /*if(reader->isEmptyFile())
    {
        handler << "Ошибка чтения файла! Файл пуст.";
        exit(-1);
    }*/
    source = reader->readFull();
    reader->close();
    if (strlen(source) <= 1) {
        handler.error() << "Исходный файл пуст.\n";
        return;
    }
    if (!checkHeadDefine() || !checkBraketsAndLastSemicolon() || !readAndCheckFields())
        return;
    handler.error() << "OK";
}

bool StructDefineValidator::checkHeadDefine() {

    source = strstr(source, "struct");
    if (source == nullptr || !isspace(source[6])) {
        handler.error() << "Определение структурного типа в исходном файле не найдено.\n";
        return false;
    }

    char *tmp = source + 6;
    char *structName = new char[257];
    int len = 0;

    while (isspace(*tmp) && &tmp)
        tmp++;
    while (*tmp && *tmp != '{' && len < 256)
        structName[len++] = *tmp++;
    structName[len] = '\0';
    if (!checkName(structName)) {
        delete structName;
        return false;
    }
    delete structName;

}

bool StructDefineValidator::checkName(const char *name) {
    char *clearName = new char[257];
    const int nameLen = strlen(name);
    register int i = 0;
    for (; i < nameLen && !isspace(*(name + i)); i++)
        *(clearName + i) = *(name + i);
    *(clearName + i) = '\0';

    for (; i < nameLen; i++)
        if (!isspace(*(name + i))) {
            handler.error() << "Ошибка определения в идентификаторе (" << name << ").\n";
            delete clearName;
            return false;
        }

    if (!(isalpha(*clearName) || *clearName == '_')) {
        handler.error() << "Ошибка определения в индетификаторе (" << clearName << "). Неверный формат.\n";
        delete clearName;
        return false;
    }
    const int clearNameLen = strlen(clearName);
    if (clearNameLen > 255) {
        handler.error() << "Ошибка определения в идентификаторе (" << clearName <<
        "). Длинная имени не должна превышать 255.\n";
        delete clearName;
        return false;
    }

    for (int i = 1; i < clearNameLen; i++)
        if (!(isalpha(*(clearName + i)) || isdigit(*(clearName + i)) || *(clearName + i) == '_')) {
            handler.error() << "Ошибка определения в индетификаторе (" << clearName << "). Неверный формат.\n";
            delete clearName;
            return false;
        }

    for (int i = 0; i < KEY_WORDS_COUNT; i++)
        if (!strcmp(clearName, keyWordsHolder->getWord(i))) {
            handler.error() << "Ошибка определения в индетификаторе (" << clearName <<
            "). Совпадение с ключевым словом.\n";
            delete clearName;
            return false;
        }
    delete clearName;
    return true;

}


bool StructDefineValidator::checkBraketsAndLastSemicolon() {
    char *openBraket = strchr(source, '{');
    if (openBraket == nullptr) {
        handler.error() << "Ошибка опредления структуры. Отсутствие '{'.\n";
        return false;
    }
    char *nextOpenBraket = strchr(openBraket + 1, '{');
    if (nextOpenBraket != nullptr) {
        handler.error() << "Ошибка определения структуры. Неверный формат.\n";
        return false;
    }

    char *closeBraket = strchr(source, '}');
    if (closeBraket == nullptr) {
        handler.error() << "Ошибка опредления структуры. Отсутствие '}'.\n";
        return false;
    }
    closeBraket++;
    bool semicolonCheked = false;
    while (*closeBraket) {
        if (*closeBraket == ';')
            semicolonCheked = true;
        else if (!isspace(*closeBraket)) {
            handler.error() << "Ошибка определения структуры. Неверный формат.\n";
            return false;
        }
        closeBraket++;
    }
    if (!semicolonCheked)
        handler.error() << "Ошибка определения структуры. Отсутсвие ';'.\n";
    return semicolonCheked;
}


bool StructDefineValidator::readAndCheckFields() {
    SimpleStringVector nameCache;
    source = strchr(source, '{');
    source++;
    while (isspace(*source))
        source++;
    if (*source == '}') {
        handler.warn() << "Опредлена структура без полей.\n";
        return false;
    }


    char *fieldType = new char[10];
    char *fieldName = new char[257];
    bool readType = true;
    bool emptyName = true;
    int i = 0;
    bool ok = true;
    while (*source != '}' && ok) {
        if (readType) {
            if (i >= 10) {
                fieldType[9] = '\0';
                handler.error() <<
                "Недопустимое количество символов в типе. Длинна не может превосходить 10 символов. Начало недопустимого типа:(" <<
                fieldType <<
                ").\n";
                return false;
            }
            if (!isspace(*source) && *source != ';')
                fieldType[i++] = *source;
            else if (i) {
                fieldType[i] = '\0';
                i = 0;
                if (!checkType(fieldType))
                    ok = false;
                readType = false;
                emptyName = true;
            }
        }
        else {
            if (i >= 255) {
                handler.error() << "Ошибка определения в идентификаторе (" << fieldName <<
                "). Длинная имени не должна превышать 255.\n";
            }
            if (emptyName) {
                if (!isspace(*source) && *source != ';') {
                    emptyName = false;
                    fieldName[i++] = *source;
                }
                else if (*source == ';') {
                    handler.error() << "У поля типа (" << fieldType << ") не найден идентификатор.\n";
                    ok = false;
                    continue;
                }

            }
            else {
                if (*source != ';')
                    fieldName[i++] = *source;
                else {
                    readType = true;
                    fieldName[i] = '\0';
                    i = 0;
                    if (!checkName(fieldName))
                        ok = false;
                    if (nameCache.contains(fieldName)) {
                        handler.error() << "Идентификатор " << fieldName << " уже определен.";
                        ok = false;
                        continue;
                    }
                    nameCache.add(fieldName);
                }
            }

        }
        source++;
    }
    delete fieldName;
    delete fieldType;
    return ok;

}

bool StructDefineValidator::checkType(const char *type) {
    bool contains = false;
    char **types = keyWordsHolder->getArrayOfTypes();
    for (int i = 0; i < TYPES_COUNT; i++)
        if (!strcmp(type, types[i]))
            contains = true;
    if (!contains)
        handler.error() << "Недопустимый тип данных. (" << type << ")\n";
    return contains;
}
