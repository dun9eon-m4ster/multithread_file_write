#include "datagenerator.h"
#include <iostream>
#include "threadshareddata.h"

DataGenerator::DataGenerator(std::shared_ptr<ThreadSharedData> _new_shared_data)
    : SharedDataTaskThread(_new_shared_data)
{

}

DataGenerator::~DataGenerator()
{
    join();
    std::cout << "DataGenerator::~DataGenerator()" << std::endl;
}

void DataGenerator::process()
{
    std::unique_lock<std::mutex> lk(_data->_mutex);

    std::cout << "DataGenerator::process()" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    _data->setFlag(ThreadSharedData::PendingData);

    lk.unlock();
    _data->_cv.notify_one();

    for(;;);
}
