#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "taskthread.h"
#include <vector>

struct Data;

class DataGenerator : public SharedDataTaskThread
{
public:
    explicit DataGenerator(std::shared_ptr<ThreadSharedData> _new_shared_data, unsigned int tick);
    ~DataGenerator();
    virtual void process() override;

private:
    std::vector<std::shared_ptr<Data>> buffer;
    std::vector<std::shared_ptr<Data>>::iterator buffer_iterator;
    double generation_sleep_duration;
};

#endif // DATAGENERATOR_H
