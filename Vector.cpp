//
// Created by usern1 on 08.11.2021.
//

#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Vector.h"

struct Vector {
    double x, y, z;

    Vector() : x(0.0), y(0.0), z(0.0) { }

    Vector(double x, double y, double z) : x(x), y(y), z(z) { }

    double length() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector operator+(const Vector& rhs) const {
        return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    Vector operator*(double scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    bool operator==(const Vector& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    friend std::istream& operator>>(std::istream&, Vector&);
    friend std::ostream& operator<<(std::ostream&, Vector&);
};

std::istream& operator>>(std::istream& in, Vector& v) {
    return in >> v.x >> v.y >> v.z;
}

std::ostream& operator<<(std::ostream& out, Vector& v) {
    auto precision = out.precision();
    auto width = out.width();
    out << std::fixed << std::setw(width) << std::setprecision(precision) << v.x << "  ";
    out << std::fixed << std::setw(width) << std::setprecision(precision) << v.y << "  ";
    out << std::fixed << std::setw(width) << std::setprecision(precision) << v.z;
    return out;
}