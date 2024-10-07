#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "taskthread.h"

class FileWriter : public SharedDataTaskThread
{
public:
    explicit FileWriter(std::shared_ptr<ThreadSharedData> _new_shared_data, const size_t &_new_data_record_goal);
    ~FileWriter();
    virtual void process() override;

private:
    size_t data_recorded;
    size_t data_record_goal;
};

#endif // FILEWRITER_H
