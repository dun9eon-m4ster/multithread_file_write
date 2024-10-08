#include "progressbar.h"

ProgressBar::ProgressBar(const unsigned int &_new_tick_count)
    : _tick_count(_new_tick_count)
{

}

std::string ProgressBar::make(const double &percentage)
{
    std::string result;
    result.push_back('[');
    for(unsigned int i = 0; i < _tick_count; i++)
    {
        if(i*100/static_cast<double>(_tick_count) < percentage)
            result.push_back('#');
        else
            result.push_back('_');
    }
    result.push_back(']');

    std::string percent_str = std::to_string(percentage);
    while (percent_str.size() > 5)
    {
        percent_str.erase(percent_str.end()-1);
    }

    result += " " + percent_str + " %";

    return result;
}
