#pragma once

#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include <chrono>
#include <thread>

namespace Visualization{

class OpenCVVisualizer {
public:
    constexpr const static auto delay = std::chrono::milliseconds(20);

    OpenCVVisualizer(std::string window_name = "Visualization", size_t h = 300, size_t w = 400);

    ~ OpenCVVisualizer();

private:

    void OnLoop();

    std::thread window_thread_;
    std::string window_;
    cv::Mat image_;

    size_t h_, w_;
    std::string window_name_;
};

}