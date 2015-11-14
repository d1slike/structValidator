#include <conio.h>
#include "files/FileReader.h"
#include "handlers/ErrorHandler.h"
#include "handlers/Validator.h"

int main(int argc, char** argv)
{
    FileReader* file = new FileReader(argv[1]);
    Validator validator(file, new ErrorHandler());
    validator.valid();
    getch();
    return 0;
}