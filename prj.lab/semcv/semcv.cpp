#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "semcv.hpp"


std::string getMatTypeString(int type) {
    switch (type) {
        case CV_8U:  return "uint08";
        case CV_8S:  return "sint08";
        case CV_16U: return "uint16";
        case CV_16S: return "sint16";
        case CV_32S: return "sint32";
        case CV_32F: return "real32";
        case CV_64F: return "real64";
        default:     return "unknown";
    }
}

std::string formatNumber(int num, int width) {
    std::string str = std::to_string(num);
    return std::string(width - str.length(), '0') + str;
}

std::string strid_from_mat(const cv::Mat& img, const int n) {
    if (img.empty()) {
        std::cerr << "Error: image is not uploaded!" << std::endl;
    }

    std::string result = formatNumber(img.cols, n) + "x" + formatNumber(img.rows, n) +
        "." + std::to_string(img.channels()) + "." 
        + getMatTypeString(img.depth());
     
    return result;
}

std::vector<std::filesystem::path> get_list_of_file_paths(const std::filesystem::path& path_lst) {
    namespace fs = std::filesystem;
    if (!fs::exists(path_lst)) {
        std::cerr << "No .lst file found :( ";
    }

    std::ifstream file(path_lst.string());
    std::vector<fs::path> file_paths;
    std::array<std::string, 3> extensions = {".tiff", ".png", ".jpg"};
    std::string s;
    while (std::getline(file, s)) {
        for (const auto& extension: extensions) {
            file_paths.push_back(fs::path(s + extension));
        }
    }
    file.close();
    return file_paths;
}

cv::Mat gen_tgtimg00(const int lev0, const int lev1, const int lev2) {
    cv::Mat res(OUTER_SQ_PIXELS, OUTER_SQ_PIXELS, CV_8UC1, cv::Scalar(lev0));

    int inner_rect_coords_y = (OUTER_SQ_PIXELS - INNER_SQ_PIXELS) / 2;
    int inner_rect_coords_x = inner_rect_coords_y;
    cv::Rect rect(
        inner_rect_coords_x, inner_rect_coords_y, 
        INNER_SQ_PIXELS, INNER_SQ_PIXELS
    );

    cv::Point center(res.rows / 2, res.cols / 2);
    cv::rectangle(res, rect, lev1, -1);
    cv::circle(res, center, CIRCLE_RADIUS, cv::Scalar(lev2), -1);
    return res;
}

cv::Mat add_noise_gau(const cv::Mat& img, const int std, const int mean) {
    cv::Mat res;
    cv::Mat noise(img.size(), img.type());
    cv::randn(noise, mean, std);
    cv::add(img, noise, res);
    return res; 
}

fs::path resolve_result_dir(const char* path_name, std::string filename) {
    fs::path path = fs::path(path_name);
    fs::path closest_parent_path = path.parent_path().filename();
    fs::path save_path = BASE_DIR / "results" / closest_parent_path / fs::path(filename);
    return save_path;
}