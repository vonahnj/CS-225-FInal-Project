#pragma once 

#include <vector>
#include <utility>

namespace encounters {
    struct date {
        int day;
        int month;
        int year;

        date() : day(1), month(1), year(0) {}
        date(int d, int m, int y) : day(d), month(m), year(y) {}
    };

    struct encounter {
        struct edge {
            encounter &start;
            encounter &end;
            double dist;

            edge(encounter &s, encounter &e) : start(s), end(e), dist(0) {}
            edge(encounter &s, encounter &e, double d) : start(s), end(e), dist(d) {}
            bool operator<(const encounter::edge &other) { return dist < other.dist; }
        };

        date time;
        std::vector<edge> time_neighbors;
        std::vector<edge> loc_neighbors;
        std::pair<double, double> location;

        encounter() : location(0, 0) {}
        encounter(date t, double longit, double latit) : time(t), location(longit, latit) {}
    };

    bool operator<(const date &first, const date &second);
    bool operator==(const date &first, const date &second);
    bool operator!=(const date &first, const date &second);
    bool operator==(const encounter::edge &first, const encounter::edge &second);

    bool operator==(const encounter &first, const encounter &second);
    double dist(const date &first, const date &second);
    double dist(const encounter &first, const encounter &second);
}