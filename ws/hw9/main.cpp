// This includes all of the necessary header files in the toolbox
#include "AMPCore.h"
#include "hw/HW2.h"
#include "KinoRRT.h"
#include "HelpfulClass.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

using namespace amp;

void writeWaypointsToCSV(const std::vector<Eigen::VectorXd>& waypoints, const std::string& filename) {
    std::ofstream file(filename); // Open file for writing

    if (file.is_open()) {
        for (const auto& waypoint : waypoints) {
            for (int i = 0; i < waypoint.size(); ++i) {
                file << waypoint(i);
                if (i < waypoint.size() - 1) {
                    file << ","; // Add comma separator between elements
                }
            }
            file << "\n"; // Start a new line for the next waypoint
        }
        file.close(); // Close the file
        std::cout << "Waypoints written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}


void problem1() {
    Problem2D problem = HW2::getWorkspace1();
    vector<pair<double, double>> stateLimits = {{problem.x_min, problem.x_max}, {problem.y_min, problem.y_max}, 
                                                {0, 2.0*M_PI}, {-1/6.0, 1/2.0}, {-M_PI/6.0, M_PI/6.0}};
    vector<pair<double, double>> controlLimits = {{-1.0/6.0, 1.0/2.0}, {-M_PI/6.0, M_PI/6.0}};

    Eigen::VectorXd initState(5);
    initState << problem.q_init(0), problem.q_init(1), 0.0, 0.0, 0.0;
    MyKinoChecker kinoChecker(problem, stateLimits, 0.5, 1);
    KinoRRT RRTplanner(2500, 0.5, 0.05, controlLimits);
    amp::Path path = RRTplanner.plan(initState, problem.q_goal, kinoChecker);
    if (path.waypoints.size() != 0) {
        Path2D path2d;
        for (const VectorXd point : path.waypoints) path2d.waypoints.push_back({point(0), point(1)});
        Visualizer::makeFigure(problem, path2d);
        writeWaypointsToCSV(path.waypoints, "waypoints.csv");
    }
}

int main(int argc, char** argv) {
    // problem1();
    problem1();
    Visualizer::showFigures();
    return 0;
}