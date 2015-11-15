#include <conio.h>
#include <locale.h>
#include "files/FileReader.h"
#include "handlers/ErrorHandler.h"
#include "handlers/StructDefineValidator.h"

int main(int argc, char **argv) {
    setlocale(LC_ALL, ".1251");
    FileReader *file = new FileReader(argv[1]);
    StructDefineValidator validator(file, new ErrorHandler());
    validator.valid();
    getch();
    return 0;
}