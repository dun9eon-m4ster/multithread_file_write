#include "threadshareddata.h"




ThreadSharedData::ThreadSharedData()
    : flags(None)
{}

void ThreadSharedData::setFlag(const ThreadSharedData::Flags &_new_flags, bool on)
{
    if(on)
        flags = static_cast<Flags>(flags | _new_flags);
    else
        flags = static_cast<Flags>(flags & ~_new_flags);
}

bool ThreadSharedData::isFlag(const ThreadSharedData::Flags &_flags_to_check) const
{
    return flags & _flags_to_check;
}
