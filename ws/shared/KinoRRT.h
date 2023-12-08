#include "AMPCore.h"
#include "HelpfulClass.h"
#include "MyCollisionCheckers.h"

using namespace amp;
using std::vector, Eigen::VectorXd, std::pair;

class KinoRRT {
    public:
        KinoRRT(int n, double r, double p, vector<pair<double, double>> controlLimits)
        : n(n), r(r), p(p), controlLimits(controlLimits) {}
        amp::Path plan(const VectorXd& init_state, const VectorXd& goal_state, MyKinoChecker& collision_checker); 
        VectorXd getRandomPoint(const vector<pair<double, double>>& limits);
        VectorXd propagateState(const VectorXd& x_start, const VectorXd& u, double& duration, MyKinoChecker& collision_checker);
        double distanceMetric(const VectorXd& state1, const VectorXd& state2);
        pair<int, Eigen::VectorXd> findNearest(const Eigen::VectorXd& point);
    private:
        int n;
        double r, p;
        double eps = 0.5;
        std::map<uint32_t, VectorXd> points;
        std::map<uint32_t, uint32_t> parents;
        std::map<uint32_t, VectorXd> controls;
        vector<pair<double, double>> controlLimits;
};