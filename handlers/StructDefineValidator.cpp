//
// Created by DisDev on 14.11.2015.
//

#include <string.h>
#include <ctype.h>
#include "StructDefineValidator.h"
#include "../collections/SimpleStringVector.h"

void StructDefineValidator::valid() {
    if (!reader->isReady()) {
        handler.error() << "Ошибка чтения файла! Файл отсутствует\n";
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
    printf("Код корректен.\n\n%s", source);
}

bool StructDefineValidator::checkHeadDefine() {

    source = strstr(source, "struct");
    if (source == nullptr || !isspace(source[6])) {
        handler.error() << INVALID_STRUCT_MESSAGE << "Определение структурного типа в исходном файле не найдено.\n";
        return false;
    }

    char *tmp = source + 6;
    char *structName = new char[257];
    int len = 0;

    while (isspace(*tmp) && *tmp)
        tmp++;
    while (*tmp && *tmp != '{' && len < 256)
        structName[len++] = *tmp++;
    structName[len] = '\0';
    if (!strlen(structName)) {
        typeGlobalDefine = false;
        delete structName;
        return true;
    }
    else if (!checkName(structName)) {
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
            handler.error() << INVALID_NAME_MESSAGE << "(" << name << ").\n";
            delete clearName;
            return false;
        }

    if (!(isalpha(*clearName) || *clearName == '_')) {
        handler.error() << INVALID_NAME_MESSAGE << "(" << clearName << "). Неверный формат.\n";
        delete clearName;
        return false;
    }
    const int clearNameLen = strlen(clearName);
    if (clearNameLen > 255) {
        handler.error() << INVALID_NAME_MESSAGE << "(" << clearName <<
        "). Длинная имени не должна превышать 255.\n";
        delete clearName;
        return false;
    }

    for (int i = 1; i < clearNameLen; i++)
        if (!(isalpha(*(clearName + i)) || isdigit(*(clearName + i)) || *(clearName + i) == '_')) {
            handler.error() << INVALID_NAME_MESSAGE << "(" << clearName << "). Неверный формат.\n";
            delete clearName;
            return false;
        }

    for (int i = 0; i < KEY_WORDS_COUNT; i++)
        if (!strcmp(clearName, keyWordsHolder->getWord(i))) {
            handler.error() << INVALID_NAME_MESSAGE << "(" << clearName <<
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
        handler.error() << INVALID_STRUCT_MESSAGE << "Отсутствие '{'.\n";
        return false;
    }
    char *nextOpenBraket = strchr(openBraket + 1, '{');
    if (nextOpenBraket != nullptr) {
        handler.error(source, nextOpenBraket) << INVALID_STRUCT_MESSAGE << "Недопустимый символ({).\n";
        return false;
    }

    char *closeBraket = strchr(source, '}');
    if (closeBraket == nullptr) {
        handler.error() << INVALID_STRUCT_MESSAGE << "Отсутствие '}'.\n";
        return false;
    }

    /*char *nextCloseBraket = strchr(closeBraket + 1, '}');
    if (nextCloseBraket != nullptr) {
        handler.error(source, nextCloseBraket) << INVALID_STRUCT_MESSAGE << "Недопустимый символ({).\n";
        return false;
    }*/
    char *name = new char[257];
    int i = 0;

    closeBraket++;
    bool isCorrect = false;
    while (*closeBraket) {
        if (*closeBraket == ';') {
            isCorrect = true;
        }
        else if (isCorrect && !isspace(*closeBraket)) {
            handler.error(source, closeBraket) << INVALID_STRUCT_MESSAGE << "Недопустимый символ (" << *closeBraket <<
            ")\n";
            return false;
        }
        else if (!isspace(*closeBraket) && i < 256) {
            /*handler.error(source, closeBraket) << INVALID_STRUCT_MESSAGE << "Недопустимый символ '" << *closeBraket <<
            ")\n";
            return false;*/
            name[i++] = *closeBraket;
        }
        closeBraket++;
    }
    name[i] = '\0';
    if (!isCorrect)
        handler.error() << INVALID_STRUCT_MESSAGE << "Отсутсвие ';'.\n";
    if (!typeGlobalDefine) {
        if (!strlen(name))
            handler.warn() << "Определена анонимная стркутура.\n";
        else
            isCorrect = checkName(name);
    }
    delete[] name;
    return isCorrect;
}


bool StructDefineValidator::readAndCheckFields() {
    SimpleStringVector nameCache;
    char *copyOfSource = strchr(source, '{');
    copyOfSource++;
    while (isspace(*copyOfSource))
        copyOfSource++;
    if (*copyOfSource == '}') {
        handler.warn() << "Опредлена структура без полей.\n";
        return false;
    }

    char *fieldType = new char[10];
    char *fieldName = new char[257];
    bool readType = true;
    bool emptyName = true;
    int i = 0;
    bool ok = true;
    bool findSpace = false;
    bool lastNameCheked = false;

    while ((*copyOfSource != '}' || !lastNameCheked) && ok) {
        if (readType) {
            if (i >= 10) {
                fieldType[9] = '\0';
                handler.error(source, copyOfSource) << INVALID_NAME_MESSAGE
                <<
                "Недопустимое количество символов в типе. Длинна не может превосходить 10 символов. Начало недопустимого типа:(" <<
                fieldType <<
                ").\n";
                return false;
            }
            if (!isspace(*copyOfSource) && *copyOfSource != ';')
                fieldType[i++] = *copyOfSource;
            else if (i) {
                fieldType[i] = '\0';
                i = 0;
                if (!checkType(fieldType))
                    ok = false;
                readType = false;
                emptyName = true;
                continue;
            }
        }
        else {
            if (i >= 255) {
                handler.error(source, copyOfSource) << INVALID_NAME_MESSAGE << "(" << fieldName <<
                "). Длинная имени не должна превышать 255.\n";
            }
            if (emptyName) {
                if (!isspace(*copyOfSource) && *copyOfSource != ';') {
                    emptyName = false;
                    fieldName[i++] = *copyOfSource;
                }
                else if (*copyOfSource == ';') {
                    handler.error(source, copyOfSource) << INVALID_NAME_MESSAGE << "У поля типа (" << fieldType <<
                    ") не найден идентификатор.\n";
                    ok = false;
                    continue;
                }

            }
            else {
                lastNameCheked = false;
                if (*copyOfSource != ';') {
                    if (isspace(*copyOfSource)) {
                        findSpace = true;
                    }
                    if (!isspace(*copyOfSource) && findSpace) {
                        handler.error(source, copyOfSource) << INVALID_STRUCT_MESSAGE << "Отсутствие ;\n";
                        ok = false;
                        continue;
                    } else if (!findSpace)
                        fieldName[i++] = *copyOfSource;
                }
                else {
                    readType = true;
                    fieldName[i] = '\0';
                    i = 0;
                    if (!checkName(fieldName)) {
                        ok = false;
                        continue;
                    }
                    if (nameCache.contains(fieldName)) {
                        handler.error(source, copyOfSource) << INVALID_NAME_MESSAGE << "Идентификатор " << fieldName <<
                        " уже определен.\n";
                        ok = false;
                        continue;
                    }
                    nameCache.add(fieldName);
                    lastNameCheked = true;
                }
            }

        }
        copyOfSource++;
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
        handler.error() << INVALID_STRUCT_MESSAGE << "Недопустимый тип данных. (" << type << ")\n";
    return contains;
}
