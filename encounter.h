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
            encounter &start;
            encounter &end;
            double dist;

            edge(encounter &s, encounter &e) : start(s), end(e), dist(0) {}
            edge(encounter &s, encounter &e, double d) : start(s), end(e), dist(d) {}
            bool operator<(const encounter::edge &other) { return dist < other.dist; }
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

    bool operator==(const encounter &first, const encounter &second);
    double dist(const date &first, const date &second);
    double dist(const encounter &first, const encounter &second);

} // namespace encounters