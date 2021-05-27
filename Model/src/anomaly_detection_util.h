
#ifndef ANOMALYDETECTORUTIL_H_
#define ANOMALYDETECTORUTIL_H_
#include <memory>


float avg(float const* x, int size);


// returns the variance of X and Y
float var(float const* x, int size);

// returns the covariance of X and Y
float cov(float const* x, float const* y, int size);


// returns the Pearson correlation coefficient of X and Y
float pearson(float const* x, float const* y, int size);

class Line {
public:
	float a, b;
	Line(float a, float b) :a(a), b(b) {}
	Line() :a(0), b(0) {}
	float f(float x) {
		return a * x + b;
	}
};

class Point {
public:
	float x, y;
	Point(float x, float y) :x(x), y(y) {}
	Point() :x(0), y(0) {}
	Point(Point* p) :x(p->x), y(p->y) {}
	Point(const Point& p) :x(p.x), y(p.y) {}
	virtual ~Point() {}


};

// performs a linear regression and returns the line equation
Line linear_reg(std::shared_ptr<Point>* points, int size);

Line linear_reg(Point** points, int size);

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point** points, int size);

float dev(Point p, std::shared_ptr<Point>* points, int size);

// returns the deviation between point p and the line
float dev(Point p, Line l);

#endif
