#ifndef BEST_TIME_H
#define BEST_TIME_H

#include <vector>
#include "distance.hpp"
#include "ttime.h"

class Best_time
{
public:
    Best_time();
    std::vector <std::vector<std::pair<path, int>>> dijkstra(const std::vector<std::vector<path>>&, const int&, const int&, TTime&);
    int get_time_cost();
    
private:
    int bus_time;
    int taxi_time;
    int subway_time;

    int bus_dilay = 15;
    int taxi_dilay = 5;
    int subway_dilay = 8;

    int time_cost = 0;
};

#endif // BEST_TIME_H
