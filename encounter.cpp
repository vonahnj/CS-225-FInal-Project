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
        
        double absolute = abs(rad * c);
        return (int)(absolute * 10000)/10000.0; // Round to the nearest decimeter
    }

    bool operator==(const encounter::edge &first, const encounter::edge &second) {
        // Compare distance, minimum end, and maximum end
        return first.dist == second.dist && 
               std::min(first.start_id, first.end_id) == std::min(second.start_id, second.end_id) &&
               std::max(first.start_id, first.end_id) == std::max(second.start_id, second.end_id);
    }

    bool operator!=(const encounter::edge &first, const encounter::edge &second) {
        return !(first == second);
    }

    bool operator<(const encounter::edge &first, const encounter::edge &second) {
        // Compare distance if different
        if (first.dist != second.dist) {
            return first.dist < second.dist;
        } 
        
        // Compare minimum end if different
        size_t firstMin = std::min(first.start_id, first.end_id);
        size_t secondMin = std::min(second.start_id, second.end_id);
        if (firstMin != secondMin) {
            return firstMin < secondMin;
        }

        // Compare maximum end
        size_t firstMax = std::max(first.start_id, first.end_id);
        size_t secondMax = std::max(second.start_id, second.end_id);
        return firstMax < secondMax;
    }

    bool operator>(const encounter::edge &first, const encounter::edge &second) {
        //Compare distance if different
        if (first.dist != second.dist) {
            return first.dist > second.dist;
        }

        // Compare a minimum end if different
        size_t firstMin = std::min(first.start_id, first.end_id);
        size_t secondMin = std::min(second.start_id, second.end_id);
        if (firstMin != secondMin) {
            return firstMin > secondMin;
        }

        // Compare minimum end
        size_t firstMax = std::max(first.start_id, first.end_id);
        size_t secondMax = std::max(second.start_id, second.end_id);
        return firstMax > secondMax;
    }

    bool operator==(const encounter &first, const encounter &second) {
        // Compare id, location, and number of neighbors
        if (first.location != second.location ||
            first.neighbors.size() != second.neighbors.size() ||
            first.id != second.id) {
            return false;
        }

        // Compare edges
        for (size_t i = 0; i < first.neighbors.size(); i++) {
            if (first.neighbors.at(i) != second.neighbors.at(i)) {
                return false;
            }
        }

        return true;
    }

    std::ostream & operator<<(std::ostream &out, const encounter &e) {
        return out<<e.id<<".) Location: ("<<e.location.first<<", "<<e.location.second<<")"<<"\t Description: "<<e.description;
    }
}
