#include "Point.h"

Point::Point() : x_(0), y_(0), z_(0) {}
Point::Point(double px, double py, double pz) : x_(px), y_(py), z_(pz) {}

const double & Point::x() const { return x_; }
const double & Point::y() const { return y_; }
const double & Point::z() const { return z_; }

double & Point::x() { return x_; }
double & Point::y() { return y_; }
double & Point::z() { return z_; }

double Point::dot(const Point & p) const {
	return x_ * p.x() + y_ * p.y() + z_ * p.z();
}

Point Point::cross(const Point & p) const {
	return Point(y_ * p.z() - z_ * p.y(),
		z_ * p.x() - x_ * p.z(),
		x_ * p.y() - y_ * p.x());
}

Point Point::unit(void) const {
	double lenSq = dot(*this);
	double len = sqrt(lenSq);
	double lenInv = 1 / len;
	return Point(lenInv * x_, lenInv * y_, lenInv * z_);
}

// convenience function to draw this as a point using OpenGL
void Point::glv(void) const { glVertex3d(x_, y_, z_); }
// convenience function to draw this as a normal
void Point::gln(void) const { glNormal3d(x_, y_, z_); }