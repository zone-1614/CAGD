#include <iostream>
#include "../util.h"

// degree elevation 算法
std::vector<point> degree_elevation(const std::vector<point>& ps, int times = 1) {
    std::vector<point> points = ps;
    while (times--) {
        auto ps_ = points;
        points.clear();
        points.resize(ps_.size() + 1);
        points.front() = ps_.front();
        points.back() = ps_.back();
        const int n = ps_.size();
        for (int i = 1; i < n; i++) {
            points[i] = i / (double)(n + 1) * ps_[i - 1] + (1.0 - i / (double)(n + 1)) * ps_[i];
        }
    }
    return points;
}

int main() {
    auto ps = read_obj();
    auto new_ps = degree_elevation(ps);
    write_obj(new_ps, "elevation.obj");
}