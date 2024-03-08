#include "../include/distance.hpp"
#include <limits.h>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector <path> Distance::dijkstra(const vector<vector<path>>&distance_data, const int &src, const int &des){
    
    int V = 59;
    vector <path> ans(V);

    map <int, bool> visited;

    priority_queue<pair<int, pair<path, int>>, vector<pair<int, pair<path, int>>>, comparePairs> z;

    path x(src);

    z.push(make_pair(0, make_pair(x, 0)));

    while (!z.empty()) {

        if (visited [z.top().second.first.end] == false){
            ans[z.top().second.first.end] = (z.top().second.first);
            visited [z.top().second.first.end] = true;
            visited [z.top().second.first.start] = true;
            if (z.top().second.first.end == des && total_distance==0) total_distance = z.top().first;
        }
        //the number of edges of the desired vertex
        int edg_num = distance_data[z.top().second.first.end].size();
        for (int i=0 ; i<edg_num; i++) {
            int cost_distance = distance_data[z.top().second.first.end][i].length;
            cost_distance += z.top().first;
            if (visited [distance_data[z.top().second.first.end][i].end] == false){
                z.push(make_pair(cost_distance, make_pair(distance_data[z.top().second.first.end][i] , z.top().second.first.tp)));
            }
        }
        
        z.pop();
    }
    return ans;
}

int Distance::get_total_distance(){
    return total_distance;
}
