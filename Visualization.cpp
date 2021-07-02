#include "Visualization.hpp"

#include <utility>

namespace Visualization {

Visualization::OpenCVVisualizer::OpenCVVisualizer(std::string window_name, size_t h,
                                                  size_t w) : window_name_(std::move(window_name)), w_(w), h_(h) {
    auto Start = [this]() {
        window_ = "Visualization";

        image_ = cv::Mat::zeros(h_, w_, CV_8UC3);

        cv::namedWindow(window_name_); // Create a window

        cv::imshow(window_name_, image_);
        cv::moveWindow(window_name_, 200, 200);

        OnLoop();
    };
    std::thread window_thread(Start);
    window_thread_ = std::move(window_thread);
};

Visualization::OpenCVVisualizer::~OpenCVVisualizer() {
    window_thread_.join();
}

void Visualization::OpenCVVisualizer::OnLoop() {
    auto last = std::chrono::system_clock::now();
    int center = 0;
    while (true) {
        std::cout << 1 << std::endl;

        auto current = std::chrono::system_clock::now();
        if (current - last < delay) {
            if (cv::waitKey(5) != -1) {
                break;
            }
            continue;
        }

        image_ = cv::Mat::zeros(h_, w_, CV_8UC3);
        cv::circle(image_, {static_cast<int>((center += 5) % w_), static_cast<int>(w_ / 2)}, w_ / 32,
                   cv::Scalar(0, 0, 255), cv::FILLED, cv::LINE_8);

        cv::imshow(window_, image_);
        last = current;
    }
}

}