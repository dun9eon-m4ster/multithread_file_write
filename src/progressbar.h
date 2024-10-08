#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <string>

class ProgressBar
{
public:
    ProgressBar(const unsigned int &_new_tick_count);
    std::string make(const double &percentage);

private:
    unsigned int _tick_count;
};

#endif // PROGRESSBAR_H
