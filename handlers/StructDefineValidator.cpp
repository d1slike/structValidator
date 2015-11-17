//
// Created by DisDev on 14.11.2015.
//

#include <string.h>
#include <ctype.h>
#include "StructDefineValidator.h"
#include "../collections/SimpleStringVector.h"

void StructDefineValidator::valid() {
    if (!reader->isReady()) {
        handler.error() << "������ ������ �����! ���� �����������\n";
        exit(-1);
    }
    /*if(reader->isEmptyFile())
    {
        handler << "������ ������ �����! ���� ����.";
        exit(-1);
    }*/
    source = reader->readFull();
    reader->close();
    if (strlen(source) <= 1) {
        handler.error() << "�������� ���� ����.\n";
        return;
    }
    if (!checkHeadDefine() || !checkBraketsAndLastSemicolon() || !readAndCheckFields())
        return;
    printf("��� ���������.\n\n%s", source);
}

bool StructDefineValidator::checkHeadDefine() {

    source = strstr(source, "struct");
    if (source == nullptr || !isspace(source[6])) {
        handler.error() << INVALID_STRUCT_MESSAGE << "����������� ������������ ���� � �������� ����� �� �������.\n";
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
        handler.error() << INVALID_NAME_MESSAGE << "(" << clearName << "). �������� ������.\n";
        delete clearName;
        return false;
    }
    const int clearNameLen = strlen(clearName);
    if (clearNameLen > 255) {
        handler.error() << INVALID_NAME_MESSAGE << "(" << clearName <<
        "). ������� ����� �� ������ ��������� 255.\n";
        delete clearName;
        return false;
    }

    for (int i = 1; i < clearNameLen; i++)
        if (!(isalpha(*(clearName + i)) || isdigit(*(clearName + i)) || *(clearName + i) == '_')) {
            handler.error() << INVALID_NAME_MESSAGE << "(" << clearName << "). �������� ������.\n";
            delete clearName;
            return false;
        }

    for (int i = 0; i < KEY_WORDS_COUNT; i++)
        if (!strcmp(clearName, keyWordsHolder->getWord(i))) {
            handler.error() << INVALID_NAME_MESSAGE << "(" << clearName <<
            "). ���������� � �������� ������.\n";
            delete clearName;
            return false;
        }
    delete clearName;
    return true;

}


bool StructDefineValidator::checkBraketsAndLastSemicolon() {
    char *openBraket = strchr(source, '{');
    if (openBraket == nullptr) {
        handler.error() << INVALID_STRUCT_MESSAGE << "���������� '{'.\n";
        return false;
    }
    char *nextOpenBraket = strchr(openBraket + 1, '{');
    if (nextOpenBraket != nullptr) {
        handler.error(source, nextOpenBraket) << INVALID_STRUCT_MESSAGE << "������������ ������({).\n";
        return false;
    }

    char *closeBraket = strchr(source, '}');
    if (closeBraket == nullptr) {
        handler.error() << INVALID_STRUCT_MESSAGE << "���������� '}'.\n";
        return false;
    }

    /*char *nextCloseBraket = strchr(closeBraket + 1, '}');
    if (nextCloseBraket != nullptr) {
        handler.error(source, nextCloseBraket) << INVALID_STRUCT_MESSAGE << "������������ ������({).\n";
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
            handler.error(source, closeBraket) << INVALID_STRUCT_MESSAGE << "������������ ������ (" << *closeBraket <<
            ")\n";
            return false;
        }
        else if (!isspace(*closeBraket) && i < 256) {
            /*handler.error(source, closeBraket) << INVALID_STRUCT_MESSAGE << "������������ ������ '" << *closeBraket <<
            ")\n";
            return false;*/
            name[i++] = *closeBraket;
        }
        closeBraket++;
    }
    name[i] = '\0';
    if (!isCorrect)
        handler.error() << INVALID_STRUCT_MESSAGE << "��������� ';'.\n";
    if (!typeGlobalDefine) {
        if (!strlen(name))
            handler.warn() << "���������� ��������� ���������.\n";
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
        handler.warn() << "��������� ��������� ��� �����.\n";
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
                "������������ ���������� �������� � ����. ������ �� ����� ������������ 10 ��������. ������ ������������� ����:(" <<
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
                "). ������� ����� �� ������ ��������� 255.\n";
            }
            if (emptyName) {
                if (!isspace(*copyOfSource) && *copyOfSource != ';') {
                    emptyName = false;
                    fieldName[i++] = *copyOfSource;
                }
                else if (*copyOfSource == ';') {
                    handler.error(source, copyOfSource) << INVALID_NAME_MESSAGE << "� ���� ���� (" << fieldType <<
                    ") �� ������ �������������.\n";
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
                        handler.error(source, copyOfSource) << INVALID_STRUCT_MESSAGE << "���������� ;\n";
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
                        handler.error(source, copyOfSource) << INVALID_NAME_MESSAGE << "������������� " << fieldName <<
                        " ��� ���������.\n";
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
        handler.error() << INVALID_STRUCT_MESSAGE << "������������ ��� ������. (" << type << ")\n";
    return contains;
}
