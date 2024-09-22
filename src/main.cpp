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

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "Error: single argument (generation tick) is not provided" << std::endl;
        return 1;
    }

    std::string str(argv[1]);


    auto generation_tick = std::stoi(str);
    if(generation_tick <= 0)
    {
        std::cerr << "Error: argument (generation tick) must be > 0" << std::endl;
        return 1;
    }

    DataGenerator generator(_shared_data, generation_tick);
    generator.start();


    FileWriter writer(_shared_data);
    writer.start();


    return 0;
}
