#include "Visualization.hpp"

#include <utility>
#include <cmath>

namespace Visualization {

Visualization::OpenCVVisualizer::OpenCVVisualizer(std::string window_name, size_t h, size_t w) : window_name_(
        std::move(window_name)), w_(w), h_(h) {
    auto Start = [this]() {
        cv::namedWindow(window_name_); // Create a window
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

    cv::Mat background = cv::Mat::zeros(h_, w_, CV_8UC3);

    while (true) {

        auto current = std::chrono::system_clock::now();
        auto delta = current - last;

        if (delta < delay) {
            if (cv::waitKey(5) != -1) {
                break;
            }
            continue;
        }

        std::cout << duration_cast<std::chrono::milliseconds>(delta).count() << "\n";

        auto image_to_show = background.clone();
//        cv::circle(image_to_show, {static_cast<int>((center += 5) % w_), static_cast<int>(w_ / 2)}, w_ / 32,
//        cv::Scalar(0, 0, 255), cv::FILLED, cv::LINE_8);
        DrawAll(image_to_show);

        cv::imshow(window_name_, image_to_show);
        last = current;
    }
}

void OpenCVVisualizer::DrawAll(cv::Mat & canvas) {

    for (const auto & object : objects_) {
        object->Draw(canvas);
    }
}

void OpenCVVisualizer::AddOpenCVModel(std::shared_ptr<OpenCVGraphicsObject> object_ptr) {
    objects_.push_back(object_ptr);
}

void Visualization::OpenCVGraphicsObject::Draw(cv::Mat & canvas) const {
    std::cout << "Not implemented!" << std::endl;
}

void Visualization::OpenCVRobotModel::Draw(cv::Mat & canvas) const {
    std::cout << "Drawing\n";

    const double truck_length = 0.1;
    const double truck_width = 0.05;
    const double pendulum_length = 0.2;
    const double pendulum_d = 0.05;

    size_t x1_int = canvas.cols * (x + truck_position);
    size_t x2_int = x1_int + canvas.cols * truck_length;
    size_t y1_int = canvas.rows * y;
    size_t y2_int = y1_int + canvas.rows * truck_width;
    cv::Point2d pt1(x1_int, y1_int);
    cv::Point2d pt2(x2_int, y2_int);
    cv::rectangle(canvas, pt1, pt2, cv::Scalar(0, 0, 255), cv::FILLED, cv::LINE_8);

    cv::Point2d center((x1_int + x2_int) / 2, y1_int);
    cv::Point2d tail(center.x + cos(pendulum_position) * pendulum_length,
                     center.y + sin(pendulum_position) * pendulum_length);
    cv::line(canvas, center, tail, cv::Scalar(255, 255, 255), 3);
}

}
