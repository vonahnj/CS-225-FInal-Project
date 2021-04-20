#include "encounter.h"
#include <math.h>
#include <iostream>

namespace encounters {
    double dist(const date &first, const date &second) {
        int day1 = first.day;
        int month1 = first.month;
        int year1 = first.year;

        int day2 = second.day;
        int month2 = second.month;
        int year2 = second.year;

        month1 = (month1 + 9) % 12;
        year1 = year1 - month1/10;

        month2 = (month2 + 9) % 12;
        year2 = year2 - month2/10;

        double no_of_days1 = (365*year1) + year1/4 - year1/100 + year1/400 + (306*month1 + 5)/10 + day1 - 1;
        double no_of_days2 = (365*year2) + year2/4 - year2/100 + year2/400 + (306*month2 + 5)/10 + day2 - 1;
        return abs(no_of_days2 - no_of_days1);
    }

    double dist(const encounter &first, const encounter &second) {
        return dist(first.location, second.location);
    }

    double dist(const std::pair<double, double> &first, const std::pair<double, double> &second) {
        // Implementing Haversine formula to determine Great Circle distance
        double lat1 = first.first;
        double lat2 = second.first;
        double lon1 = first.second;
        double lon2 = second.second;

        double dLat = (lat2 - lat1) *
                      M_PI / 180.0;
        double dLon = (lon2 - lon1) * 
                      M_PI / 180.0;
  
        // convert to radians
        lat1 *= (M_PI / 180.0);
        lat2 *= (M_PI / 180.0);
  
        // apply formulae
        double a = pow(sin(dLat / 2), 2) + 
                   pow(sin(dLon / 2), 2) * 
                   cos(lat1) * cos(lat2);
        double rad = 6371;
        double c = 2 * asin(sqrt(a));
        return abs(rad * c);
    }

    bool operator<(const date &first, const date &second) {
        if (first.year != second.year) {
            return first.year < second.year;
        } else if (first.month != second.month) {
            return first.month < second.month;
        } 
        return first.month < second.month;
    }

    bool operator==(const encounter::edge &first, const encounter::edge &second) {
        return first.dist == second.dist && 
               std::min(first.start_id, first.end_id) == std::min(second.start_id, second.end_id) &&
               std::max(first.start_id, first.end_id) == std::max(second.start_id, second.end_id);
    }

    bool operator!=(const encounter::edge &first, const encounter::edge &second) {
        return !(first == second);
    }

    bool operator<(const encounter::edge &first, const encounter::edge &second) {
        return first.dist < second.dist;
    }

    bool operator>(const encounter::edge &first, const encounter::edge &second) {
        return first.dist > second.dist;
    }

    bool operator==(const date &first, const date &second) {
        return first.year == second.year && first.month == second.month && first.day == second.day;
    }

    bool operator!=(const date &first, const date &second) {
        return !(first == second);
    }

    bool operator==(const encounter &first, const encounter &second) {
        if (first.time != second.time || first.location != second.location ||
            first.loc_neighbors.size() != second.loc_neighbors.size() ||
            first.time_neighbors.size() != second.time_neighbors.size() ||
            first.id != second.id) {
            return false;
        }

        std::vector<encounter::edge> firstNeighbors = first.loc_neighbors;
        sort(firstNeighbors.begin(), firstNeighbors.end());
        std::vector<encounter::edge> secondNeighbors = second.loc_neighbors;
        sort(secondNeighbors.begin(), secondNeighbors.end());

        for (size_t i = 0; i < firstNeighbors.size(); i++) {
            if (firstNeighbors.at(i) != secondNeighbors.at(i)) {
                return false;
            }
        }

        firstNeighbors = first.time_neighbors;
        sort(firstNeighbors.begin(), firstNeighbors.end());
        secondNeighbors = second.time_neighbors;
        sort(secondNeighbors.begin(), secondNeighbors.end());

        for (size_t i = 0; i < firstNeighbors.size(); i++) {
            if (firstNeighbors.at(i) != secondNeighbors.at(i)) {
                return false;
            }
        }

        return true;
    }

    std::ostream & operator<<(std::ostream &out, const date &d) {
        return out<<d.month<<'/'<<d.day<<'/'<<d.year;
    }
    std::ostream & operator<<(std::ostream &out, const encounter &e) {
        return out<<e.id<<'\t'<<e.time<<"\t("<<e.location.first<<", "<<e.location.second<<")";
    }
}
