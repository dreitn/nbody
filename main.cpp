#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "Vector.cpp"

struct Body {
    double mass;
    Vector position;
    Vector velocity;
    Vector acceleration;
};

class NBody {
private:
    double gc; // gravity
    int timeSteps;
    std::vector<Body> bodies;

public:
    void simulate() {
        computeAccelerations();
        computePositions();
        computeVelocities();
        resolveCollisions();
    }

private:
    void computeAccelerations() {
        for (int i = 0; i < bodies.size(); ++i) {
            bodies[i].acceleration = Vector();
            for (int j = 0; j < bodies.size(); ++j) {
                if (i != j) {
                    double temp = gc * bodies[j].mass / pow((bodies[i].position - bodies[j].position).length(), 3);
                    bodies[i].acceleration = bodies[i].acceleration + (bodies[j].position - bodies[i].position) * temp;
                }
            }
        }
    }

    void computeVelocities() {
        for (int i = 0; i < bodies.size(); ++i) {
            bodies[i].velocity = bodies[i].velocity + bodies[i].acceleration;
        }
    }

    void computePositions() {
        for (int i = 0; i < bodies.size(); ++i) {
            bodies[i].position = bodies[i].position + bodies[i].velocity + bodies[i].acceleration * 0.5;
        }
    }

    void resolveCollisions() {
        for (int i = 0; i < bodies.size(); ++i) {
            for (int j = i + 1; j < bodies.size(); ++j) {
                if (bodies[i].position == bodies[j].position) {
                    std::swap(bodies[i].velocity, bodies[j].velocity);
                }
            }
        }
    }

public:
    NBody(std::string& fileName) {
        std::ifstream is(fileName);

        if (!is.is_open()) {
            throw std::runtime_error("Could not open file.");
        }

        int size = 0;
        is >> gc >> size >> timeSteps;

        double m;
        Vector p, v;
        for (int i = 0; i < size; ++i) {
            is >> m >> p >> v;
            bodies.push_back(Body{.mass = m, .position = p, .velocity = v});
        }

        std::cout << "Contents of " << fileName << '\n';
        std::cout << gc << ' ' << size << ' ' << timeSteps << '\n';
        for (int i = 0; i < bodies.size(); ++i) {
            std::cout << bodies[i].mass << '\n' << bodies[i].position << '\n' << bodies[i].velocity << '\n';
        }
        std::cout << "\nBody   :      x          y          z    |     vx         vy         vz";
    }

    int getTimeSteps() {
        return timeSteps;
    }

    friend std::ostream& operator<<(std::ostream& out, NBody& nb) {
        for (int i = 0; i < nb.bodies.size(); ++i) {
            out << "Body " << i + 1 << " : ";
            out << std::setprecision(6) << std::setw(9) << nb.bodies[i].position;
            out << " | ";
            out << std::setprecision(6) << std::setw(9) << nb.bodies[i].velocity;
            out << '\n';
        }
        return out;
    }
};

int main() {
    std::string fileName = "nbody.txt";
    NBody nb(fileName);

    for (int i = 0; i < nb.getTimeSteps(); ++i) {
        std::cout << "\nCycle " << i + 1 << '\n';
        nb.simulate();
        std::cout << nb;
    }
    return 0;
}