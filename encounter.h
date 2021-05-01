#pragma once 

#include <vector>
#include <ostream>
#include <utility>

namespace encounters {
    /**
     */
    struct encounter {
        /**
         */
        struct edge {
            int start_id;
            int end_id;
            double dist;

            edge() : start_id(-1), end_id(-1), dist(0) {}
            edge(int start, int end) : start_id(start), end_id(end), dist(0) {}
            edge(int start, int end, double d) : start_id(start), end_id(end), dist(d) {}
        };

        size_t id;
        std::vector<edge> neighbors;
        std::pair<double, double> location;

        encounter() : id(0), location(0, 0) {}
        encounter(double latit_, double longit_, size_t id_) : id(id_), location(latit_, longit_) {}
    };

    /**
     * Prints the encounter out into the given ostream
     * @param out the ostream the encounter must be added to
     * @param d the encounter to be printed
     * @return the ostream with the encounter added
     */
    std::ostream & operator<<(std::ostream &out, const encounter &e);

    /**
     * Functions to compare edges. 
     * (a < b) or (b > a) => 
     *  Checks the following attributes and returns the 
     *  comparision of the first one that is different: 
     *      1. Distance
     *      2. Minimum End ID
     *      3. Maximum End ID
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