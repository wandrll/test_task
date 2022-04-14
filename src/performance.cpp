#include "pool.hpp"

#include <iostream>
#include <chrono>
#include <ctime>

template<typename Func>
void RunFunction(bool measure_time, const std::string& message, Func function) {


    if (measure_time) {
        auto start = std::chrono::system_clock::now();

        function();

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;
        std::cout << message << ": " << elapsed_time.count() << " seconds" << std::endl;

    } else {
        function();
        std::cout << message << std::endl;
    }
}


void PerformanceTest(long long pools_cnt, long long channels_cnt, long long water_add_cnt, bool measure_time, int max_adding_water = 100){
    Pool* pools = new Pool[pools_cnt];


    RunFunction(true, "Initial adding water in each pool ",[=]{
        for (auto i = 0; i < pools_cnt; i++){
            pools[i].Add(std::rand() % max_adding_water);
        }
    });


    RunFunction(true, "Connect random pools via channels ",[=]{
        for (auto i = 0; i < channels_cnt; i++){
            pools[std::rand() % pools_cnt].Connect(pools[std::rand() % pools_cnt]);
        }
    });


    RunFunction(true, "Measure pools ",[=]{
        for (auto i = 0; i < pools_cnt; i++){
            auto curr_level = pools[i].Measure();
        }
    });


    RunFunction(true, "Add random amount of water in random pools ",[=]{
        for (auto i = 0; i < water_add_cnt; i++){
            pools[std::rand() % pools_cnt].Add(std::rand() % max_adding_water);
        }
    });



    RunFunction(true, "Again measure pools ",[=]{
        for (auto i = 0; i < pools_cnt; i++){
            auto curr_level = pools[i].Measure();
        }
    });


    delete[] pools;
}





int main () {
    std::srand(std::time(nullptr));

    RunFunction(true, "Successfully completed in ", []{
        PerformanceTest(8000000, 12000000, 40000000, true, 1000);
    });

}
