#include <conio.h>
#include <locale.h>
#include "files/FileReader.h"
#include "handlers/ErrorHandler.h"
#include "handlers/Validator.h"
#include "holders/KeyWordsArray.h"

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");
    FileReader* file = new FileReader(argv[1]);
    Validator validator(file, new ErrorHandler());
    validator.valid();
    getch();
    return 0;
}