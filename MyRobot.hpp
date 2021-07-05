#pragma once

#include <ct/core/core.h>
#include <ct/models/InvertedPendulum/codegen/InvertedPendulumActDynLinearizedForward.h>

#include <eigen3/Eigen/Eigen>
#include <chrono>
#include "Visualization.hpp"

class Robot {
private:

    using Pendulum = ct::models::InvertedPendulum::InvertedPendulumActDynLinearizedForward;
//    Pendulum::;

    class PhysicalModel {
        PhysicalModel(double truck_m, double pendulum_m, double pendulum_l);

        std::vector<double> IntegrateDT(const std::vector<double> & x, double acceleration,
                                        std::chrono::milliseconds dt_ms);

        double GetBestForceLQR(const std::vector<double> & x);

        double truck_m_;
        double pendulum_m_;
        double pendulum_l_;
    };

    void StartMoving();

public:
    void StartShowing(Visualization::OpenCVVisualizer & visualizer);
    void OnLoop();

    std::vector<double> position;



};