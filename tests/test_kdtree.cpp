#include "../cs225/catch/catch.hpp"

#include "../encounter.h"
#include "../kd_tree/kdtree.h"
#include "../kd_tree/point.h"

#include <vector>

using namespace encounters;

void destroyEncounterVec2(vector<encounter*> &vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        delete vec.at(i);
    }
}

TEST_CASE("Test smallerDimVal", "[kdtree]") {
    KDTree tree;
    Point<2> a(1, 2);
    Point<2> b(3, 2);

    REQUIRE( tree.smallerDimVal(a, b, 0) == true );
    REQUIRE( tree.smallerDimVal(a, b, 1) == true );
}

TEST_CASE("Test findNearestNeighbor 1", "[kdtree]") {
    KDTree tree;

    Point<2> target(1, 3);
    Point<2> currentBest1(1, 3);
    Point<2> possibleBest1(2, 4);
    Point<2> currentBest2(1, 4);
    Point<2> possibleBest2(2, 4);
    Point<2> currentBest3(2, 4);
    Point<2> possibleBest3(1, 4);

    REQUIRE( tree.shouldReplace(target, currentBest1, possibleBest1) == false );
    REQUIRE( tree.shouldReplace(target, currentBest2, possibleBest2) == false );
    REQUIRE( tree.shouldReplace(target, currentBest3, possibleBest3) == true ); 
    
}

TEST_CASE("Test findNearestNeighbor 2", "[kdtree]") {
    double coords[6][2] = {
        {-15, 7}, {6, 7}, {-13, -1},
        {-5, 0}, {14, -3}, {14, 2}
    };
    double targetCoords[2] = {-13, 1};
    double expectedCoords[2] = {-13, -1};

    vector<encounter*> points;
    for (int i = 0; i < 6; ++i){
        points.push_back(new encounter(date(), coords[i][0], coords[i][1], i));
    }
    Point<2> target(targetCoords);
    int expected = 2;

    KDTree tree(points);
    int size = 2;
    int K = 2;
    REQUIRE( tree.findNearestNeighbor(target) == expected );

    destroyEncounterVec2(points);
}