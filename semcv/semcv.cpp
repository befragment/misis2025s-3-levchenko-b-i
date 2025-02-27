#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <opencv2/core.hpp>
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
    std::vector<std::filesystem::path> list_of_file_paths;
    std::vector<std::string> list_of_file_names;

	if (fs::exists(path_lst) && fs::is_directory(path_lst)) {
        std::string s; 
        std::ifstream file(path_lst.string() + "\\task01.lst");
        
        while (std::getline(file, s)) {
            list_of_file_names.push_back(s);
        }

        file.close();

        for (const auto& entry : fs::directory_iterator(path_lst)) {
            if (std::find(
                    list_of_file_names.begin(), list_of_file_names.end(), entry.path().stem()
                ) != list_of_file_names.end()) {
                list_of_file_paths.push_back(entry.path());
            } 
        }
	} else {
        std::cerr << "Can't open file or directory. " <<
            "Path '" << path_lst << "' is not coorect!" << std::endl;
    }

    return list_of_file_paths.empty() ? std::vector<fs::path>{} : list_of_file_paths;
}

