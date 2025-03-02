#pragma once
#ifndef SEMCV_HPP

#include <iostream>
#include <filesystem>

#define OUTER_SQ_PIXELS 256
#define INNER_SQ_PIXELS 209
#define CIRCLE_RADIUS 83

namespace fs = std::filesystem;

std::string strid_from_mat(const cv::Mat& img, const int n = 4);
std::vector<fs::path> get_list_of_file_paths(const fs::path& path_lst);
cv::Mat gen_tgtimg00(const int lev0, const int lev1, const int lev2);
cv::Mat add_noise_gau(const cv::Mat& img, const int std = 25.0, const int mean = 0.0);

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec) {
    os << '[';
    for (int i = 0; i < vec.size() - 1; i++) {
        os << vec[i] << ", ";
    }
    os << vec[vec.size() - 1] << ']' << std::endl;
    return os;
}

// defined in root CMakeLists.txt
const static fs::path BASE_DIR = fs::path(PRJ_ROOT_DIR); 
const static fs::path RESULTS_DIR = fs::path(PRJ_RESULTS_DIR); 
//

#endif