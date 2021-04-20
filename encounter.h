#pragma once 

#include <vector>
#include <ostream>
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
            int start_id;
            int end_id;
            double dist;

            edge(int start, int end) : start_id(start), end_id(end), dist(0) {}
            edge(int start, int end, double d) : start_id(start), end_id(end), dist(d) {}
        };

        date time;
        size_t id;
        std::vector<edge> time_neighbors;
        std::vector<edge> loc_neighbors;
        std::pair<double, double> location;

        encounter() : id(0), location(0, 0) {}
        encounter(date time_, double latit_, double longit_, size_t id_) : time(time_), id(id_), location(latit_, longit_) {}
    };

    std::ostream & operator<<(std::ostream &out, const date &d);
    std::ostream & operator<<(std::ostream &out, const encounter &e);

    bool operator<(const date &first, const date &second);
    bool operator==(const date &first, const date &second);
    bool operator!=(const date &first, const date &second);
    bool operator==(const encounter::edge &first, const encounter::edge &second);
    bool operator!=(const encounter::edge &first, const encounter::edge &second);
    bool operator<(const encounter::edge &first, const encounter::edge &second);
    bool operator>(const encounter::edge &first, const encounter::edge &second);

    bool operator==(const encounter &first, const encounter &second);
    double dist(const date &first, const date &second);
    double dist(const encounter &first, const encounter &second);
    double dist(const std::pair<double, double> &first, const std::pair<double, double> &second);

} // namespace encounters