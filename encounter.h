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

    /**
     * Prints the date out into the given ostream
     * @param out the ostream the date must be added to
     * @param d the date to be printed
     * @return the ostream with the date added
     */
    std::ostream & operator<<(std::ostream &out, const date &d);

    /**
     * Prints the encounter out into the given ostream
     * @param out the ostream the encounter must be added to
     * @param d the encounter to be printed
     * @return the ostream with the encounter added
     */
    std::ostream & operator<<(std::ostream &out, const encounter &e);

    /**
     * Functions to compare dates. 
     * if (a < b), a occurred before b
     * if (a > b), b occurred before a
     * if (a == b), a occurred on the same day as b
     * if (a != b), a did not occur on the same day as b
     */
    bool operator<(const date &first, const date &second);
    bool operator>(const date &first, const date &second);
    bool operator==(const date &first, const date &second);
    bool operator!=(const date &first, const date &second);

    /**
     * Functions to compare edges. 
     * if (a < b), a is longer than b
     * if (a > b), b is longer than a
     * if (a == b), a connects the same nodes as b and has the same lengths
     * if (a != b), a does not connect the same nodes as b or have different lengths
     */
    bool operator==(const encounter::edge &first, const encounter::edge &second);
    bool operator!=(const encounter::edge &first, const encounter::edge &second);
    bool operator<(const encounter::edge &first, const encounter::edge &second);
    bool operator>(const encounter::edge &first, const encounter::edge &second);

    /**
     * Compares two encounters to see if they have the same date, id, location, and adjacent edges
     * 
     * This is a very costly operation so use it sparingly. Whenever possible, compare using distance or dates
     */
    bool operator==(const encounter &first, const encounter &second);

    /**
     * Calculates the distance in days between the first and second date. 
     * This function always returns a positive value
     */
    double dist(const date &first, const date &second);

    /**
     * Calculates the physical distance between the first and second encounter
     * in kilometers. 
     * This function always returns a positive value
     */
    double dist(const encounter &first, const encounter &second);

    /**
     * Calculates the physical distance between the first and second pair of GPS coordinates
     * in kilometers. 
     * This function always returns a positive value. 
     * 
     * The first element of each pair is assumed to be the latitude while the second is presumed to be its longitude
     */
    double dist(const std::pair<double, double> &first, const std::pair<double, double> &second);

} // namespace encounters