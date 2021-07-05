#pragma once

#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <memory>

namespace Visualization{

class OpenCVGraphicsObject {
public:
    OpenCVGraphicsObject() = default;
    ~OpenCVGraphicsObject() = default;

    virtual void Draw(cv::Mat& canvas) const;

protected:
    double x = 0, y = 0;
};

class OpenCVRobotModel : public OpenCVGraphicsObject{

    void Draw(cv::Mat& canvas) const override;
protected:
    double truck_position; // 0 - 1
    double pendulum_position; // 0 - 2 Pi
};

class OpenCVVisualizer {
public:
    constexpr const static auto delay = std::chrono::milliseconds(20);

    explicit OpenCVVisualizer(std::string window_name = "Visualization", size_t h = 300, size_t w = 400);

    ~ OpenCVVisualizer();

    void AddOpenCVModel(std::shared_ptr<OpenCVGraphicsObject>);

private:

    void OnLoop();
    void DrawAll(cv::Mat& canvas);

    std::thread window_thread_;
    cv::Mat image_;

    size_t h_, w_;
    std::string window_name_;

    std::vector<std::shared_ptr<OpenCVGraphicsObject> > objects_;
};

}