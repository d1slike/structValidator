#include <conio.h>
#include <locale.h>
#include "files/FileReader.h"
#include "handlers/ErrorHandler.h"
#include "handlers/StructDefineValidator.h"

int main(int argc, char **argv) {
    setlocale(LC_ALL, ".1251");
    //FileReader *file = new FileReader(argv[1]);
    StructDefineValidator validator(new FileReader(argv[1]), new ErrorHandler());
    validator.valid();
    printf("\nНажмите любую клавишу для завершения...\n");
    getch();
    return 0;
}