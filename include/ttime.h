#ifndef TIME_H
#define TIME_H

class TTime
{
public:
    TTime(const int&, const int&);
    void set_hour(const int &, const int &);
    void set_min(const int &, const int &);
    int traffic_time(const int&);
    int add_time_h(const int&);
    int add_time_m(const int&);

private:
    int hour;
    int minute;
};

#endif // TIME_H
