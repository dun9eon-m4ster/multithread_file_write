#include "filewriter.h"
#include <iostream>
#include "threadshareddata.h"

FileWriter::FileWriter(std::shared_ptr<ThreadSharedData> _new_shared_data)
    : SharedDataTaskThread(_new_shared_data)
{

}

FileWriter::~FileWriter()
{
    join();
    std::cout << "FileWriter::~FileWriter()" << std::endl;
}

void FileWriter::process()
{
    std::unique_lock<std::mutex> lk(_data->_mutex);
    _data->_cv.wait(lk, [this]{return _data->isFlag(ThreadSharedData::PendingData);});

    std::cout << "FileWriter::process()" << std::endl;

    for(;;);
}
