//This class is responsible for the communication between backend and UI.
#ifndef SEMANHASHT_H
#define SEMANHASHT_H

#include <QObject>
#include <unordered_map>
#include "cost.h"
#include "best_time.h"
#include "distance.hpp"
#include "resetpath.h"
#include <stack>

class Semanhasht : public QObject
{
    Q_OBJECT
public:
    explicit Semanhasht(QObject *parent = nullptr);

public slots: 
    void set_objects(QObject*, int, int);
    void direction(int, int, const int&, const int&);
    void show_path (int, int, int);
    void set_map(const QString&, const int&);
    int check_station_validation(const QString&);
    void print_path(const int&, const int&, TTime&);
    QString get_q_time_path();
    QString get_q_cost_path();
    QString get_q_distance_path();

signals:

private:
    std::vector <std::vector<QObject*>>objects = std::vector <std::vector<QObject*>> (59);

    std::unordered_map <std::string, int> stationToIndex;
    std::unordered_map <int, std::string> indexToStation;

    std::vector<std::vector<path>> distance_data;

    Distance distance;
    std::vector <path> distance_path;
    QString q_distance_path; //prints the path

    Cost cost;
    std::vector <std::vector<std::pair<path, int>>> cost_path;
    QString q_cost_path; //prints the path

    Best_time best_time;
    std::vector <std::vector<std::pair<path, int>>> time_path;
    QString q_time_path; //prints the path

    std::stack<path> print_pathS;

    ResetPath RP;

};

#endif // SEMANHASHT_H
