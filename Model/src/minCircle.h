// 316294842 206586687
#ifndef MINCIRCLEW_H_
#define MINCIRCLEW_H_

#include "anomaly_detection_util.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "math.h"

using namespace std;

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};

// calculates the distance between two points
float dist(Point p1, Point p2);

// returns the min circle that surrounds the two points
Circle twoPointsCircle(Point p1, Point p2);

// returns the min circle that surrounds the three points
Circle threePointsCircle(Point p1, Point p2, Point p3);

// returns the min circle that this one point
Circle trivialCircle(vector<Point> R);

// findes the minimal circle that surrounds all of this points
Circle welzl(Point** P, vector<Point> R ,size_t size);

// findes the minimal circle that surrounds all of this points using the welzl's algorithm
Circle findMinCircle(Point** points,size_t size);






#endif /* MINCIRCLEW_H_ */