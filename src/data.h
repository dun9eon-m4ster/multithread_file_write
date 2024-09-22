#ifndef DATA_H
#define DATA_H

struct Data
{
    enum{size = 1048576}; ///< 1MB
    unsigned char buffer[size];
};

#endif // DATA_H
