#include "encounter.h"
#include <math.h>

namespace encounters {
    double dist(const date &first, const date &second) {
        int yearDiff = first.year - second.year;
        int monthDiff = first.month - second.month;
        int dayDiff = first.day - second.day;
        return abs((int)(yearDiff*365.25) + (int)(monthDiff*30.5) + dayDiff);
    }

    double dist(const encounter &first, const encounter &second) {
        // Implementing Haversine formula to determine Great Circle distance
        double lat1 = first.location.first;
        double lat2 = second.location.first;
        double lon1 = first.location.second;
        double lon2 = second.location.second;

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
        return rad * c;
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
        return first.dist == second.dist && &(first.start) == &(second.start) && &(first.end) == &(second.end);

    }

    bool operator==(const date &first, const date &second) {
        return first.year == second.year && first.month == second.month && first.day == second.day;
    }

    bool operator!=(const date &first, const date &second) {
        return !(first == second);
    }

    bool operator==(const encounter &first, const encounter &second) {
        if (first.time != second.time || first.location != second.location) {
            return false;
        }

        if (first.loc_neighbors != second.loc_neighbors) {
            return false;
        }

        return first.time_neighbors != second.time_neighbors;
    }

    std::ostream & operator<<(std::ostream &out, const date &d) {
        return out<<d.month<<'/'<<d.day<<'/'<<d.year;
    }
    std::ostream & operator<<(std::ostream &out, const encounter &e) {
        return out<<e.time<<"\t("<<e.location.first<<", "<<e.location.second<<")";
    }
}
