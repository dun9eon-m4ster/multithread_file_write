#include "datagenerator.h"
#include "filewriter.h"

int main()
{
    DataGenerator generator;
    generator.start();

    FileWriter writer;
    writer.start();


    return 0;
}
