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
    if(argc != 3)
    {
        std::cerr << "Error: argument count mismatch: expected 2, have " << argc-1 << std::endl;
        return 1;
    }

    auto generation_tick = std::stoi(argv[1]);
    if(generation_tick <= 0)
    {
        std::cerr << "Error: 1st argument (generation tick) must be > 0" << std::endl;
        return 1;
    }

    auto data_record_goal = std::stol(argv[2]);
    if(data_record_goal <= 0)
    {
        std::cerr << "Error: 2nd argument (data record goal) must be > 0" << std::endl;
        return 1;
    }

    DataGenerator generator(_shared_data, generation_tick);
    generator.start();


    FileWriter writer(_shared_data, data_record_goal);
    writer.start();


    return 0;
}
