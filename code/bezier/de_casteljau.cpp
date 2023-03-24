#include <iostream>
#include "../util.h"

// de Casteljau 算法
std::vector<point> decas(const std::vector<point>& ps, double step = 0.001) {
    std::vector<point> points;
    for (double t = 0.0; t < 1.0; t += step) {
        std::vector<point> ps_ = ps;
        while (ps_.size() != 1) {
            for (int i = 0; i < ps_.size() - 1; i++) {
                ps_[i] = ps_[i] * (1 - t) + ps_[i + 1] * t;
            }
            ps_.pop_back();
        }
        points.push_back(ps_.front());
    }
    return points;
}

int main() {
    // auto ps = read_obj("elevation_input.obj");
    // auto interpolate = decas(ps);
    // write_obj(interpolate, "elevation_output.obj");
    auto ps = read_obj();
    auto interpolate = decas(ps);
    write_obj(interpolate);
}