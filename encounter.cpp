#include "encounter.h"
#include <math.h>

namespace encounters {
    double dist(const date &first, const date &second) {
        int day1 = first.day;
        int month1 = first.month;
        int year1 = first.year;

        int day2 = second.day;
        int month2 = second.month;
        int year2 = second.year;

        if (month1 <= 2) {
            month1 += 12;
            year1 -= 1;
        }            
        
        if(month2 <= 2) {
            month2 += 12;
            year2 -= 1;
        }
        int no_of_days1 = (146097*year1)/400 + (153*month1 + 8)/5 + day1;
        int no_of_days2 = (146097*year2)/400 + (153*month2 + 8)/5 + day2;
        return abs(no_of_days2 - no_of_days1);
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
}