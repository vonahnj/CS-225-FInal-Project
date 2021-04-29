#include "encounter.h"
#include <math.h>
#include <iostream>

namespace encounters {
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

    bool operator==(const encounter &first, const encounter &second) {
        if (first.location != second.location ||
            first.neighbors.size() != second.neighbors.size() ||
            first.id != second.id) {
            return false;
        }

        std::vector<encounter::edge> firstNeighbors = first.neighbors;
        sort(firstNeighbors.begin(), firstNeighbors.end());
        std::vector<encounter::edge> secondNeighbors = second.neighbors;
        sort(secondNeighbors.begin(), secondNeighbors.end());

        for (size_t i = 0; i < firstNeighbors.size(); i++) {
            if (firstNeighbors.at(i) != secondNeighbors.at(i)) {
                return false;
            }
        }

        return true;
    }

    std::ostream & operator<<(std::ostream &out, const encounter &e) {
        return out<<e.id<<"\t("<<e.location.first<<", "<<e.location.second<<")";
    }
}
