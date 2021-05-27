//#include "pch.h"
#include "anomaly_detection_util.h"

/*
 * anomaly_detection_util.cpp
 *
 * Author: 206586687 Shaked Or
 */

#include "cmath"
#include <iostream>
#include "string.h"

float avg(float const* x, int size) {
	float sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += x[i];
	}
	return sum / size;
}

// returns the variance of X and Y
float var(float const* x, int size) {
	float mean = avg(x, size);
	float sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += pow(x[i], 2);
	}
	return (sum / size) - pow(mean, 2);
}

// returns the covariance of X and Y
float cov(float const* x, float const* y, int size) {
	float sum = 0;
	float meanX = avg(x, size);
	float meanY = avg(y, size);
	for (int i = 0; i < size; i++)
	{
		sum += (x[i] - meanX) * (y[i] - meanY);
	}
	return sum / size;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float const* x, float const* y, int size) {

	return cov(x, y, size) / (sqrt(var(x, size)) * sqrt(var(y, size)));

}

// performs a linear regression and returns the line equation
Line linear_reg(std::shared_ptr<Point>* points, int size) {
	float* xPoints = new (std::nothrow) float[size];
	float* yPoints = new (std::nothrow) float[size];
	for (int i = 0; i < size; i++)
	{
		Point p = *(points[i]);
		xPoints[i] = p.x;
		yPoints[i] = p.y;
	}
	float a = cov(xPoints, yPoints, size) / var(xPoints, size);
	float b = avg(yPoints, size) - a * avg(xPoints, size);
	delete[] xPoints;
	delete[] yPoints;
	return Line(a, b);
}

Line linear_reg(Point** points, int size) {
	float* xPoints = new (std::nothrow) float[size];
	float* yPoints = new (std::nothrow) float[size];
	for (int i = 0; i < size; i++)
	{
		Point* p = points[i];
		xPoints[i] = p->x;
		yPoints[i] = p->y;
	}
	float a = cov(xPoints, yPoints, size) / var(xPoints, size);
	float b = avg(yPoints, size) - a * avg(xPoints, size);
	delete[] xPoints;
	delete[] yPoints;
	return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, std::shared_ptr<Point>* points, int size) {
	Line lineEq = linear_reg(points, size);
	return dev(p, lineEq);
}

float dev(Point p, Point** points, int size) {
	Line lineEq = linear_reg(points, size);
	return dev(p, lineEq);
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
	float expectedY = l.f(p.x);
	return std::abs(expectedY - p.y);
}