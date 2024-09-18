#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "taskthread.h"

class FileWriter : public TaskThread
{
public:
    ~FileWriter();
    virtual void process() override;
};

#endif // FILEWRITER_H
