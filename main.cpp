#include <iostream>
#include "MyRobot.hpp"
#include "Visualization.hpp"

int main() {
    Visualization::OpenCVVisualizer v("Visualization", 300, 400);

    Robot robot;
    robot.StartShowing(v);
};