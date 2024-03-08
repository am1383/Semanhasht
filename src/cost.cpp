#include "cost.h"
#include <vector>
#include <queue>
#include <map>
using namespace std;

Cost::Cost() {
    bus_cost = 2250;
    subway_cost = 3267;
    taxi_cost = 6000;
}

vector <vector<pair<path, int>>> Cost::dijkstra(vector<vector<path>>distance_data, const int &src, const int &des)
{
    int V = 59;
    vector <vector<pair<path, int>>> ans(V); 

    map <pair <int , int> , bool> visited;

    priority_queue<pair<int, pair<path, int>>, vector<pair<int, pair<path, int>>>, comparePairs> z;

    path x(src);

    z.push(make_pair(0, make_pair(x , 0)));

    while (!z.empty()) {

        if (visited [make_pair(z.top().second.first.end, z.top().second.first.tp)] == false){
            ans[z.top().second.first.end].push_back (make_pair((z.top().second.first) , z.top().second.second));
            visited [make_pair(z.top().second.first.end, z.top().second.first.tp)] = true;
            visited [make_pair(z.top().second.first.start, z.top().second.first.tp)] = true;
            if (z.top().second.first.end == des && total_cost==0) total_cost = z.top().first;

        }
        //the number of edges of the desired vertex
        int edg_num = distance_data[z.top().second.first.end].size();
        for (int i=0 ; i<edg_num; i++) {
            bool inLine = (distance_data[z.top().second.first.end][i].tp != z.top().second.first.tp || z.top().second.first.tp/10 == 2);
            int cost;
            switch (distance_data[z.top().second.first.end][i].tp/10){
                case 1:
                    cost = bus_cost;
                    break;
                case 2:
                    cost = distance_data[z.top().second.first.end][i].length * taxi_cost;
                    break;
                case 3:
                    cost = subway_cost;
                    break;
            }
            cost = cost * inLine + z.top().first;
            if (visited [make_pair(distance_data[z.top().second.first.end][i].end, distance_data[z.top().second.first.end][i].tp)] == false ){
                z.push(make_pair(cost, make_pair(distance_data[z.top().second.first.end][i] , z.top().second.first.tp)));
            }
        }
        z.pop();
    }
    return ans;
}

int Cost::get_total_cost() {return total_cost;}
