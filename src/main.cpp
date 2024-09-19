#include "datagenerator.h"
#include "filewriter.h"
#include "threadshareddata.h"

std::shared_ptr<ThreadSharedData> _shared_data(new ThreadSharedData);

int main()
{
    DataGenerator generator(_shared_data);
    generator.start();


    FileWriter writer(_shared_data);
    writer.start();


    return 0;
}
