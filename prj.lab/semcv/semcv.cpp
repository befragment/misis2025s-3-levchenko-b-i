#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "semcv.hpp"

using namespace cv;


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
