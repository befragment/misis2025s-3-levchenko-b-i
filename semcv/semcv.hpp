#pragma once
#ifndef SEMCV_HPP

#include <filesystem>

std::string strid_from_mat(const cv::Mat& img, const int n = 4);
std::vector<std::filesystem::path> get_list_of_file_paths(const std::filesystem::path& path_lst);

#endif