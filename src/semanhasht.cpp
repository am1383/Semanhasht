#include "semanhasht.h"
#include <QGuiApplication>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QString>
#include "ttime.h"

using namespace std;

void toLower(string &s){
    for(unsigned i{0}; i < s.length(); i++){
        s[i] = tolower(s[i]);
    }
}

Semanhasht::Semanhasht(QObject *parent) 
    : QObject{parent}
{
    //read distance adjacency list from file and save it to the distance_data
    ifstream file("../Semanhasht/files/distanceList.txt");
    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string token;
            vector<path> currentPaths;
            while (getline(iss, token, '$')) {
                istringstream pathStream(token);
                path instancePath;
                pathStream >> instancePath.start;
                pathStream.ignore();
                pathStream >> instancePath.end;
                pathStream.ignore();
                pathStream >> instancePath.length;
                pathStream.ignore();
                pathStream >> instancePath.tp;
                if (instancePath.tp/10 == 2){ // It includes both subway and taxi
                    path instancePath2; //subway
                    instancePath2.start = instancePath.start;
                    instancePath2.end = instancePath.end;
                    instancePath2.length = instancePath.length;
                    instancePath2.tp = instancePath.tp + 10;
                    currentPaths.push_back(instancePath2);
                }
                currentPaths.push_back(instancePath);
            }
            distance_data.push_back(currentPaths);
        }
        file.close();
    }
    else {
        cout << "Unable to open the file." << endl;
    }
}

void Semanhasht::set_objects(QObject* object, int start, int end){
    objects[start].push_back(object);
    objects[end].push_back(object);
}

void Semanhasht::set_map(const QString &station, const int &index){
    string Sstation = station.toStdString();

    toLower(Sstation);
    stationToIndex[Sstation] = index+1;
    indexToStation[index+1] = Sstation;
}

//if the station is available, it returns its index, otherwise -1
int Semanhasht::check_station_validation(const QString& station){
    string Sstation = station.toStdString();
    toLower(Sstation);
    return stationToIndex[Sstation] ? (stationToIndex[Sstation]-1) : -1;
}

void Semanhasht::direction (int src, int end, const int &th, const int &tm){
    TTime tt(th, tm); //saves the start time
    distance_path = distance.dijkstra(distance_data, src, end);
    cost_path = cost.dijkstra(distance_data, src, end);
    time_path = best_time.dijkstra(distance_data, src, end, tt);
    show_path (src, end, 3);
    print_path(src, end, tt);
}

void Semanhasht::show_path (int src, int end, int type){
    
    if (type == 1){
        RP.reset();
        path dd = distance_path[end];
        while (dd.start != src){
            for (int i=0 ; i<objects[dd.start].size(); i++){
                if (dd.tp/10 == 1){
                    if(objects[dd.start][i]->property("strokeStyle").toInt() == 2 &&
                        (objects[dd.start][i]->property("e").toInt() == dd.end ||
                         objects[dd.start][i]->property("s").toInt() == dd.end)){
                        RP.set_edges(objects[dd.start][i], objects[dd.start][i]->property("color"),objects[dd.start][i]->property("strokeWidth"));
                        objects[dd.start][i]-> setProperty("color" , "purple");
                        objects[dd.start][i]-> setProperty("strokeWidth" , 9);
                        break;
                    }
                }
                else if (dd.tp/10 != 1){
                    if(objects[dd.start][i]->property("strokeStyle").toInt() == 1 &&
                        (objects[dd.start][i]->property("e").toInt() == dd.end ||
                         objects[dd.start][i]->property("s").toInt() == dd.end)){
                        RP.set_edges(objects[dd.start][i], objects[dd.start][i]->property("color"),objects[dd.start][i]->property("strokeWidth"));
                        objects[dd.start][i]-> setProperty("color" , "purple");
                        objects[dd.start][i]-> setProperty("strokeWidth" , 9);
                        break;
                    }
                }
            }
            dd = distance_path[dd.start];
        }
        for (int i=0 ; i<objects[dd.start].size(); i++){
            if (dd.tp/10 == 1){
                if(objects[dd.start][i]->property("strokeStyle").toInt() == 2 &&
                    (objects[dd.start][i]->property("e").toInt() == dd.end ||
                     objects[dd.start][i]->property("s").toInt() == dd.end)){
                    RP.set_edges(objects[dd.start][i], objects[dd.start][i]->property("color"),objects[dd.start][i]->property("strokeWidth"));
                    objects[dd.start][i]-> setProperty("color" , "purple");
                    objects[dd.start][i]-> setProperty("strokeWidth" , 9);
                    break;
                }
            }
            else if (dd.tp/10 != 1){
                if(objects[dd.start][i]->property("strokeStyle").toInt() == 1 &&
                    (objects[dd.start][i]->property("e").toInt() == dd.end ||
                     objects[dd.start][i]->property("s").toInt() == dd.end)){
                    RP.set_edges(objects[dd.start][i], objects[dd.start][i]->property("color"),objects[dd.start][i]->property("strokeWidth"));
                    objects[dd.start][i]-> setProperty("color" , "purple");
                    objects[dd.start][i]-> setProperty("strokeWidth" , 9);
                    break;
                }
            }
        }
    }


    else if (type == 2){
        RP.reset();
        pair <path, int> dd = cost_path[end][0];

        while (dd.first.start != src) {
            for (int i=0 ; i<objects[dd.first.start].size(); i++){
                if (dd.first.tp/10 == 1){
                    if(objects[dd.first.start][i]->property("strokeStyle").toInt() == 2 &&
                        (objects[dd.first.start][i]->property("e").toInt() == dd.first.end ||
                         objects[dd.first.start][i]->property("s").toInt() == dd.first.end)){
                        RP.set_edges(objects[dd.first.start][i], objects[dd.first.start][i]->property("color"),objects[dd.first.start][i]->property("strokeWidth"));
                        objects[dd.first.start][i]-> setProperty("color" , "purple");
                        objects[dd.first.start][i]-> setProperty("strokeWidth" , 9);
                        break;
                    }
                }
                else if (dd.first.tp/10 != 1){
                    if(objects[dd.first.start][i]->property("strokeStyle").toInt() == 1 &&
                        (objects[dd.first.start][i]->property("e").toInt() == dd.first.end ||
                         objects[dd.first.start][i]->property("s").toInt() == dd.first.end)){
                        RP.set_edges(objects[dd.first.start][i], objects[dd.first.start][i]->property("color"),objects[dd.first.start][i]->property("strokeWidth"));
                        objects[dd.first.start][i]-> setProperty("color" , "purple");
                        objects[dd.first.start][i]-> setProperty("strokeWidth" , 9);
                        break;
                    }
                }
            }
            for (int i=0 ; i<cost_path[dd.first.start].size() ; i++){
                if (cost_path[dd.first.start][i].first.tp == dd.second){
                    dd = cost_path[dd.first.start][i];
                    break;
                }
            }
        }
        //first edge
        for (int i=0 ; i<objects[dd.first.start].size(); i++){
            if (dd.first.tp/10 == 1){
                if(objects[dd.first.start][i]->property("strokeStyle").toInt() == 2 &&
                    (objects[dd.first.start][i]->property("e").toInt() == dd.first.end ||
                     objects[dd.first.start][i]->property("s").toInt() == dd.first.end)){
                    RP.set_edges(objects[dd.first.start][i], objects[dd.first.start][i]->property("color"),objects[dd.first.start][i]->property("strokeWidth"));
                    objects[dd.first.start][i]-> setProperty("color" , "purple");
                    objects[dd.first.start][i]-> setProperty("strokeWidth" , 9);
                    break;
                }
            }
            else if (dd.first.tp/10 != 1){
                if(objects[dd.first.start][i]->property("strokeStyle").toInt() == 1 &&
                    (objects[dd.first.start][i]->property("e").toInt() == dd.first.end ||
                     objects[dd.first.start][i]->property("s").toInt() == dd.first.end)){
                    RP.set_edges(objects[dd.first.start][i], objects[dd.first.start][i]->property("color"),objects[dd.first.start][i]->property("strokeWidth"));
                    objects[dd.first.start][i]-> setProperty("color" , "purple");
                    objects[dd.first.start][i]-> setProperty("strokeWidth" , 9);
                    break;
                }
            }
        }
    }

    else if (type == 3){
        RP.reset();
        pair <path, int> dd = time_path[end][0];

        while (dd.first.start != src) {
            for (int i=0 ; i<objects[dd.first.start].size(); i++){
                if (dd.first.tp/10 == 1){
                    if(objects[dd.first.start][i]->property("strokeStyle").toInt() == 2 &&
                        (objects[dd.first.start][i]->property("e").toInt() == dd.first.end ||
                         objects[dd.first.start][i]->property("s").toInt() == dd.first.end)){
                        RP.set_edges(objects[dd.first.start][i], objects[dd.first.start][i]->property("color"),objects[dd.first.start][i]->property("strokeWidth"));
                        objects[dd.first.start][i]-> setProperty("color" , "purple");
                        objects[dd.first.start][i]-> setProperty("strokeWidth" , 9);
                        break;
                    }
                }
                else if (dd.first.tp/10 != 1){
                    if(objects[dd.first.start][i]->property("strokeStyle").toInt() == 1 &&
                        (objects[dd.first.start][i]->property("e").toInt() == dd.first.end ||
                         objects[dd.first.start][i]->property("s").toInt() == dd.first.end)){
                        RP.set_edges(objects[dd.first.start][i], objects[dd.first.start][i]->property("color"),objects[dd.first.start][i]->property("strokeWidth"));
                        objects[dd.first.start][i]-> setProperty("color" , "purple");
                        objects[dd.first.start][i]-> setProperty("strokeWidth" , 9);
                        break;
                    }
                }
            }
            for (int i=0 ; i<time_path[dd.first.start].size() ; i++){
                if (time_path[dd.first.start][i].first.tp == dd.second){
                    dd = time_path[dd.first.start][i];
                    break;
                }
            }
        }
        //first edge
        for (int i=0 ; i<objects[dd.first.start].size(); i++){
            if (dd.first.tp/10 == 1){
                if(objects[dd.first.start][i]->property("strokeStyle").toInt() == 2 &&
                    (objects[dd.first.start][i]->property("e").toInt() == dd.first.end ||
                     objects[dd.first.start][i]->property("s").toInt() == dd.first.end)){
                    RP.set_edges(objects[dd.first.start][i], objects[dd.first.start][i]->property("color"),objects[dd.first.start][i]->property("strokeWidth"));
                    objects[dd.first.start][i]-> setProperty("color" , "purple");
                    objects[dd.first.start][i]-> setProperty("strokeWidth" , 9);
                    break;
                }
            }
            else if (dd.first.tp/10 != 1){
                if(objects[dd.first.start][i]->property("strokeStyle").toInt() == 1 &&
                    (objects[dd.first.start][i]->property("e").toInt() == dd.first.end ||
                     objects[dd.first.start][i]->property("s").toInt() == dd.first.end)){
                    RP.set_edges(objects[dd.first.start][i], objects[dd.first.start][i]->property("color"),objects[dd.first.start][i]->property("strokeWidth"));
                    objects[dd.first.start][i]-> setProperty("color" , "purple");
                    objects[dd.first.start][i]-> setProperty("strokeWidth" , 9);
                    break;
                }
            }
        }
    }
}

void Semanhasht::print_path(const int &src, const int &end, TTime &tt){

    pair <path, int> dd = time_path[end][0];
    while (dd.first.start != src) {
        print_pathS.push(dd.first);
        for (int i=0 ; i<time_path[dd.first.start].size() ; i++){
            if (time_path[dd.first.start][i].first.tp == dd.second){
                dd = time_path[dd.first.start][i];
                break;
            }
        }
    }
    print_pathS.push(dd.first);

    string spath;
    int tpTemp = 0;

    while (!print_pathS.empty()){
        if (print_pathS.top().tp != tpTemp){
            spath = indexToStation[print_pathS.top().start+1] + " ";
            q_time_path = q_time_path + QString::fromStdString(spath);
            switch (print_pathS.top().tp/10) {
            case 1:
                q_time_path = q_time_path + QString::fromUtf8("\xF0\x9F\x9A\x8C") + " ";
                break;
            case 2:
                q_time_path = q_time_path + QString::fromUtf8("\xF0\x9F\x9A\x95") + " ";
                break;
            case 3:
                q_time_path = q_time_path + QString::fromUtf8("\xF0\x9F\x9A\x85") + " ";
                break;
            }
            tpTemp = print_pathS.top().tp;
        }
        if (print_pathS.size() == 1){
            spath = indexToStation[print_pathS.top().end+1] + " ";
            q_time_path = q_time_path + QString::fromStdString(spath);
        }
        print_pathS.pop();
    }
    if (best_time.get_time_cost() != 0) spath = "\n\ntime cost : " + to_string(best_time.get_time_cost());
    q_time_path = q_time_path + QString::fromStdString(spath);
    spath = "    arriving time :  " + to_string(tt.add_time_h(best_time.get_time_cost())) + " : " + to_string(tt.add_time_m(best_time.get_time_cost()));
    q_time_path = q_time_path + QString::fromStdString(spath);

    int cost_ARtime = 0;
    dd = cost_path[end][0];
    while (dd.first.start != src) {
        print_pathS.push(dd.first);
        for (int i=0 ; i<cost_path[dd.first.start].size() ; i++){
            if (cost_path[dd.first.start][i].first.tp == dd.second){
                dd = cost_path[dd.first.start][i];
                break;
            }
        }
    }

    print_pathS.push(dd.first);

    tpTemp = 0;

    while (!print_pathS.empty()){
        int Traffic_time = tt.traffic_time(cost_ARtime);
        if (print_pathS.top().tp != tpTemp){
            spath = indexToStation[print_pathS.top().start+1] + " ";
            q_cost_path = q_cost_path + QString::fromStdString(spath);
            switch (print_pathS.top().tp/10) {
            case 1:
                q_cost_path = q_cost_path + QString::fromUtf8("\xF0\x9F\x9A\x8C") + " ";
                cost_ARtime += 15 + 15*(Traffic_time == 1);
                break;
            case 2:
                q_cost_path = q_cost_path + QString::fromUtf8("\xF0\x9F\x9A\x95") + " ";
                cost_ARtime += 5 + 5*(Traffic_time == 2);
                break;
            case 3:
                q_cost_path = q_cost_path + QString::fromUtf8("\xF0\x9F\x9A\x85") + " ";
                cost_ARtime += 8 + 16*(Traffic_time == 1);
                break;
            }
        }
        switch (print_pathS.top().tp/10){
        case 1:
            cost_ARtime += print_pathS.top().length * 4;
            break;
        case 2:
            cost_ARtime += print_pathS.top().length * 2;
            break;
        case 3:
            cost_ARtime += print_pathS.top().length * 1;
            break;
        }
        if (Traffic_time==2 && print_pathS.top().tp/10 == 2){
            cost_ARtime += cost_ARtime * 2;
        }
        else if (Traffic_time==1){
            if (print_pathS.top().tp/10 == 1){
                cost_ARtime += cost_ARtime * 2;
            }
        }
        tpTemp = print_pathS.top().tp;
        if (print_pathS.size() == 1){
            spath = indexToStation[print_pathS.top().end+1] + " ";
            q_cost_path = q_cost_path + QString::fromStdString(spath);
        }
        print_pathS.pop();
    }
    if (cost.get_total_cost() != 0) spath = "\n\ncost : " + to_string(cost.get_total_cost());
    q_cost_path = q_cost_path + QString::fromStdString(spath);
    spath = "    arriving time :  " + to_string(tt.add_time_h(cost_ARtime)) + " : " + to_string(tt.add_time_m(cost_ARtime));
    q_cost_path = q_cost_path + QString::fromStdString(spath);


    int distance_ARtime = 0;
    path ss = distance_path[end];
    while (ss.start != src) {
        print_pathS.push(ss);
        ss = distance_path[ss.start];
    }

    print_pathS.push(ss);

    tpTemp = 0;

    while (!print_pathS.empty()){
        if (print_pathS.top().tp != tpTemp){
            spath = indexToStation[print_pathS.top().start+1] + " ";
            q_distance_path = q_distance_path + QString::fromStdString(spath);
            switch (print_pathS.top().tp/10) {
            case 1:
                q_distance_path = q_distance_path + QString::fromUtf8("\xF0\x9F\x9A\x8C") + " ";
                distance_ARtime += 15;
                break;
            case 2:
                q_distance_path = q_distance_path + QString::fromUtf8("\xF0\x9F\x9A\x95") + " ";
                distance_ARtime += 5;
                break;
            case 3:
                q_distance_path = q_distance_path + QString::fromUtf8("\xF0\x9F\x9A\x85") + " ";
                distance_ARtime += 8;
                break;
            }
            switch (print_pathS.top().tp/10){
            case 1:
                distance_ARtime += print_pathS.top().length * 4;
                break;
            case 2:
                distance_ARtime += print_pathS.top().length * 2;
                break;
            case 3:
                distance_ARtime += print_pathS.top().length * 1;
                break;
            }
            tpTemp = print_pathS.top().tp;
        }
        if (print_pathS.size() == 1){
            spath = indexToStation[print_pathS.top().end+1] + " ";
            q_distance_path = q_distance_path + QString::fromStdString(spath);
        }
        print_pathS.pop();
    }
    if (distance.get_total_distance() != 0) spath = "\ndistance : " + to_string(distance.get_total_distance());
    q_distance_path = q_distance_path + QString::fromStdString(spath);
    spath = "    arriving time :  " + to_string(tt.add_time_h(distance_ARtime)) + " : " + to_string(tt.add_time_m(distance_ARtime));
    q_distance_path = q_distance_path + QString::fromStdString(spath);

}

QString Semanhasht::get_q_time_path(){return q_time_path;}

QString Semanhasht::get_q_cost_path(){return q_cost_path;}

QString Semanhasht::get_q_distance_path(){return q_distance_path;}
