#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "taskthread.h"

class FileWriter : public SharedDataTaskThread
{
public:
    explicit FileWriter(std::shared_ptr<ThreadSharedData> _new_shared_data);
    ~FileWriter();
    virtual void process() override;
};

#endif // FILEWRITER_H
