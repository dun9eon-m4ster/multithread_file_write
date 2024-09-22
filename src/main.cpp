#include "datagenerator.h"
#include "filewriter.h"
#include "threadshareddata.h"
#include <iostream>

std::shared_ptr<ThreadSharedData> _shared_data(new ThreadSharedData);

class Timer
{
public:
    Timer()
    {
        start = std::chrono::steady_clock::now();
    }

    ~Timer()
    {
        auto end = std::chrono::steady_clock::now();

        std::cout << "elapsed time: " << std::chrono::duration<double>(end - start).count() << " seconds" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> start;
};

Timer t;

int main()
{
    DataGenerator generator(_shared_data, 100);
    generator.start();


    FileWriter writer(_shared_data);
    writer.start();


    return 0;
}
