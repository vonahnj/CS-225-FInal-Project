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
        return pow(pow(first.location.first - second.location.first, 2) + 
                pow(first.location.second - second.location.second, 2), 0.5);
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