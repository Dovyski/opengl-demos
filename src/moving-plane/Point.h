#ifndef		__Point_H__
#define		__Point_H__

#include <GL/freeglut.h>
#include <algorithm>
#include <cmath>

// 3D point/vector class
class Point {
public:
	// constructors
	Point();
	// z = 0 by default,to make it easier to use as 2D point
	Point(double px, double py, double pz = 0.0);
	// getters
	const double & x() const;
	const double & y() const;
	const double & z() const;
	// setters
	double & x();
	double & y();
	double & z();

	// dot product with another vector
	double dot(const Point & p) const;
	
	// cross product with another vector
	Point cross(const Point & p) const;

	// returns a unit vector of this vector
	Point unit(void) const;
	// convenience function to draw this as a point using OpenGL
	void glv(void) const;
	// convenience function to draw this as a normal
	void gln(void) const;


	// addition
	friend Point operator + (const Point & p1, const Point & p2) {
		return Point(p1.x() + p2.x(), p1.y() + p2.y(), p1.z() + p2.z());
	}

	// subtraction
	friend Point operator - (const Point & p1, const Point & p2) {
		return Point(p1.x() - p2.x(), p1.y() - p2.y(), p1.z() - p2.z());
	}

	// unary minus
	friend Point operator - (const Point & p1) {
		return Point(-p1.x(), -p1.y(), -p1.z());
	}

	// scalar product
	friend Point operator * (double a, const Point & p) {
		return Point(a * p.x(), a * p.y(), a * p.z());
	}

private:
	double x_, y_, z_;
};

#endif