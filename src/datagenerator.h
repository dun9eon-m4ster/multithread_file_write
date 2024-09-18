#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "taskthread.h"

class DataGenerator : public TaskThread
{
public:


    ~DataGenerator();
    virtual void process() override;
};

#endif // DATAGENERATOR_H
