#pragma once
#include "AMPCore.h"
using std::vector, std::string, std::cout, Eigen::Vector2d;

struct Coefficients {
	double a;
	double b;
	double c;
};

struct Points {
	Vector2d first;
	Vector2d second;
};

struct Edge {
	Coefficients coeff;
	Points points;
};

class MyClass {
    public:
        amp::Polygon findMinkowskiDiff(const amp::Obstacle2D& obstacle, std::vector<Eigen::Vector2d> robotVertices);
        std::vector<amp::Polygon> findCSpaceObstacles(const amp::Obstacle2D& obstacle, std::vector<Eigen::Vector2d> robotVertices);
};

bool isPointInsidePolygon(const Vector2d& point, const vector<Vector2d>& polygon);

double distanceBetweenPoints(const Vector2d& point1, const Vector2d& point2);

vector<vector<Edge>> findEdges(const amp::Problem2D& problem);

bool checkLine(const Vector2d& point, const Edge& egde, bool left=true);

double distanceToLine(const Vector2d& point, const Edge& egde);

Vector2d closestPointOnLine(const Vector2d& point, const Edge& egde);
