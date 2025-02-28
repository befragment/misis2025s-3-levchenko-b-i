#pragma once
#ifndef SEMCV_HPP

#include <iostream>
#include <filesystem>

std::string strid_from_mat(const cv::Mat& img, const int n = 4);
std::vector<std::filesystem::path> get_list_of_file_paths(const std::filesystem::path& path_lst);

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec) {
    os << '[';
    for (int i = 0; i < vec.size() - 1; i++) {
        os << vec[i] << ", ";
    }
    os << vec[vec.size() - 1] << ']' << std::endl;
    return os;
}

const static std::filesystem::path BASE_DIR = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path();

#endif