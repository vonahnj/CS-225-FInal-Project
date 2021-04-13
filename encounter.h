#pragma once 

#include <utility>

namespace encounters {
    struct date {
        int year;
        int month;
        int day;
    };

    struct encounter {
        date time;
        std::pair<double, double> location;
    };

    int dist(const date &first, const date &second);
    double dist(const encounter &first, const encounter &second);
}