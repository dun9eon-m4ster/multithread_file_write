#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "taskthread.h"
#include "cyclicbuffer.h"

struct Data;

class DataGenerator : public SharedDataTaskThread
{
public:
    explicit DataGenerator(std::shared_ptr<ThreadSharedData> _new_shared_data, unsigned int tick);
    ~DataGenerator();
    virtual void process() override;

private:
    CyclicBuffer<Data> buffer;
    double generation_sleep_duration;
};

#endif // DATAGENERATOR_H
