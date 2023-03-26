#include <iostream>
#include <vector>
#include <stdexcept>

#include "../util.h"
#include "../config.h"

// NURBS
point nurbs(double t, int degree, std::vector<point> points, std::vector<double> knots, std::vector<double> weights);

int main() {
    std::vector<point> ans;
    int degree = 3;
    std::vector<point> points = read_obj("nurbs_input.obj");
    std::vector<double> knots;
    std::vector<double> weights;
    knots.resize(points.size() + degree + 1);
    weights.resize(points.size());
    for (int i = 0; i < knots.size(); i++) {
        knots[i] = double(i);
    }
    for (int i = 0; i < weights.size(); i++) {
        weights[i] = 1.0;
    }
    for (double t = 0.0; t < 1.0; t += 0.01) {
        ans.push_back(nurbs(t, degree, points, knots, weights));
    }
    write_obj(ans, "nurbs.obj");
}

point nurbs(double t, int degree, std::vector<point> points, std::vector<double> knots, std::vector<double> weights) {
    if (t > 1.01 || t < 0.0) {
        throw std::logic_error("illegal <t>");
    }
    if (knots.size() != points.size() + degree + 1) {
        throw std::logic_error("illegal <knots> size");
    }
    if (weights.size() != points.size()) {
        throw std::logic_error("illegal <weights> size");
    }

    const int points_number = points.size();

    // remap the parameter <t> to the domain of spline
    const int domain[2] = { degree, knots.size() - 1 - degree };
    const double low = knots[domain[0]], high = knots[domain[1]];
    t = t * (high - low) + low;

    // find the <segment> which contains <t>
    int segment = 0;
    for (int i = domain[0]; i < domain[1]; i++) {
        if (t >= knots[i] && t <= knots[i + 1]) {
            segment = i;
            break;
        }
    }

    // convert <points> to homogeneous coordinates <homo_points>
    std::vector<vec4> homo_points(points.size());
    for (int i = 0; i < points.size(); i++) {
        homo_points[i](0) = points[i](0) * weights[i];
        homo_points[i](1) = points[i](1) * weights[i];
        homo_points[i](2) = points[i](2) * weights[i];
        homo_points[i](3) = weights[i];
    }

    // using de Boor algorithm to compute B-Spline
    for (int order = 1; order <= degree + 1; order++) {
        for (int i = segment; i > segment - degree - 1 + order; i--) {
            double f = (t - knots[i]) / (knots[i + degree + 1 - order] - knots[i]);

            homo_points[i](0) = (1 - f) * homo_points[i - 1](0) + f * homo_points[i](0);
            homo_points[i](1) = (1 - f) * homo_points[i - 1](1) + f * homo_points[i](1);
            homo_points[i](2) = (1 - f) * homo_points[i - 1](2) + f * homo_points[i](2);
            homo_points[i](3) = (1 - f) * homo_points[i - 1](3) + f * homo_points[i](3);
        }
    }

    // convert the <homo_points> to <result>
    point result;
    result(0) = homo_points[segment](0) / homo_points[segment](3);
    result(1) = homo_points[segment](1) / homo_points[segment](3);
    result(2) = homo_points[segment](2) / homo_points[segment](3);
    return result;
}
