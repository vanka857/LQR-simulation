#include "MyRobot.hpp"


void Robot::StartShowing(Visualization::OpenCVVisualizer& visualizer) {
    auto model = std::make_shared<Visualization::OpenCVRobotModel>();
    visualizer.AddOpenCVModel(model);
}

std::vector<double> Robot::PhysicalModel::IntegrateDT(const std::vector<double> & x, double acceleration,
                                                      std::chrono::milliseconds dt_ms) {
    std::vector<double> result(x);
    return result;
}

double Robot::PhysicalModel::GetBestForceLQR(const std::vector<double> & x) {
    return 0;
}

Robot::PhysicalModel::PhysicalModel(double truck_m, double pendulum_m, double pendulum_l) : truck_m_(truck_m), pendulum_m_(pendulum_m),
                                                                                            pendulum_l_(pendulum_l) {
}
