//
// Created by DisDev on 14.11.2015.
//

#include <string.h>
#include <ctype.h>
#include "Validator.h"

void Validator::valid() {
    if(!reader->isReady())
    {
        handler << "������ ������ �����! ���� ����������� ��� ����.";
        exit(-1);
    }
    /*if(reader->isEmptyFile())
    {
        handler << "������ ������ �����! ���� ����.";
        exit(-1);
    }*/
    source = reader->readFull();
    reader->close();
    //if(!checkHeadDefine() || !checkBraketsAndLastSemicolon() || !readAndCheckFields())
        return;
}

bool Validator::checkHeadDefine() {

    source = strstr(source, "struct");
    if(source == nullptr || !isspace(source[6]))
    {
        handler << "����������� ������������ ���� � �������� ����� �� �������.";
        return false;
    }

    char* tmp = source + 6;
    char* structName = new char[257];
    int len = 0;

    while(isspace(*tmp))
        tmp++;
    while(*tmp && *tmp != '{' && len < 256)
        structName[len++] = *tmp++;
    structName[len++] = '\0';
//    if(!checkName(structName, len))
        return false;
    source = strstr(structName, "{");

}

bool Validator::checkName(char *name) {
    if(!isalpha(*name) || *name != '_')
    {
        handler << "������ � ���������� ����� " << name;
        return false;
    }

}
