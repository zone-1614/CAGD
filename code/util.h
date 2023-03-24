#pragma once

#include "config.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <Eigen/Dense>

using vec3 = Eigen::Vector3d;
using point = Eigen::Vector3d;

/**
 * @brief 将 obj 文件读入并转为 std::vector<point>. 注意这个函数只是简单的读取数据, 不要有注释, 只能有顶点数据
 * @param filename 要读入的obj文件
 * @return std::vector<point> 
 */
std::vector<point> read_obj(const std::string& filename = "default_input.obj") {
    std::ifstream ifs(std::string(input_path) + filename);
    std::stringstream ss;
    std::string str;
    double v1, v2, v3;
    vec3 v;
    std::vector<point> ps;
    ss << ifs.rdbuf();
    ifs.close();
    while (ss >> str) {
        ss >> v1; ss >> v2; ss >> v3;
        v << v1, v2, v3;
        ps.push_back(v);
    }
    return ps;
}

// 将 std::vector<point> 写入为 obj 文件
void write_obj(const std::vector<point>& points, const std::string& filename = "default_output.obj") {
    std::stringstream ss;
    std::ofstream ofs(std::string(output_path) + filename);
    for (auto& p : points) {
        ss << "v ";
        ss << p[0]; ss << " ";
        ss << p[1]; ss << " ";
        ss << p[2]; ss << " ";
        ss << std::endl;
    }
    ofs << ss.rdbuf();
    ofs.close();
}
