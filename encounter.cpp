#include "encounter.h"
#include <math.h>

namespace encounters {
    int dist(const date &first, const date &second) {
        int yearDiff = first.year - second.year;
        int monthDiff = first.month - second.month;
        int dayDiff = first.day - second.day;
        return abs(yearDiff*365 + (int)(monthDiff*30.5) + dayDiff);
    }
    double dist(const encounter &first, const encounter &second) {
        return pow(pow(first.location.first - second.location.first, 2) + 
                pow(first.location.second - second.location.second, 2), 0.5);
    }
}