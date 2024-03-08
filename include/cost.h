#ifndef COST_H
#define COST_H

#include <vector>
#include "distance.hpp"

class Cost
{
public:
    Cost();
    std::vector <std::vector<std::pair<path, int>>> dijkstra(std::vector<std::vector<path>>, const int&, const int&);
    int get_total_cost();

private:
    int bus_cost;
    int subway_cost;
    int taxi_cost;

    int total_cost{0};
};

#endif // COST_H
