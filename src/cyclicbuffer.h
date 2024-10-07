#ifndef CYCLICBUFFER_H
#define CYCLICBUFFER_H

#include <memory>
#include <vector>

static const unsigned long long BUFFER_SIZE = 256;
static_assert (BUFFER_SIZE > 0, "Buffer cannot be zero");

template<typename T>
class CyclicBuffer
{
public:
    CyclicBuffer()
    {
        for(int i = 0; i < BUFFER_SIZE; i++)
        {
            buffer.push_back(std::shared_ptr<T>(new T));
        }

        it = buffer.end();
    }

    std::shared_ptr<T> put(const T &_new_data)
    {
        if(it == buffer.end())
            it = buffer.begin();

        (*(*it)) = _new_data;

        std::shared_ptr<T> _return_value = *it;

        it++;

        return _return_value;
    }

private:
    typename std::vector<std::shared_ptr<T>>::iterator it;
    std::vector<std::shared_ptr<T>> buffer;
};

#endif // CYCLICBUFFER_H
