#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "taskthread.h"

class DataGenerator : public SharedDataTaskThread
{
public:
    DataGenerator(std::shared_ptr<ThreadSharedData> _new_shared_data);
    ~DataGenerator();
    virtual void process() override;
};

#endif // DATAGENERATOR_H
