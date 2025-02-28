#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <regex>
#include <opencv2/opencv.hpp>
#include "semcv/semcv.hpp"

namespace fs = std::filesystem;

void gen_data(const fs::path& filepath) {
    int width = 256, height = 256;

    struct DataType {
        int cvType;
        std::string name;
    };

    std::vector<DataType> dtypes = {
        {CV_8U, "uint08"},
        {CV_8S, "sint08"},
        {CV_16U, "uint16"},
        {CV_16S, "sint16"},
        {CV_32S, "sint32"},
        {CV_32F, "real32"},
        {CV_64F, "real64"}
    };

    std::vector<int> channelsList = { 1, 3, 4 };
    std::vector<std::string> imgFormats = { "png", "tiff", "jpg" };
    std::cout << "lst filepath "<<filepath;
    std::ofstream lst_file(filepath);

    for (const auto& dtype : dtypes) {
        for (int channels : channelsList) {
            std::string file_data = BASE_DIR.string() + "/images" + '/' + "0256x0256." + std::to_string(channels) + "." + dtype.name;
            lst_file << file_data << '\n';
            for (const auto& imgFormat : imgFormats) {
                cv::Mat image(height, width, CV_MAKETYPE(dtype.cvType, channels), cv::Scalar(0));
                fs::path filename = BASE_DIR / "images" / fs::path(file_data + '.' + imgFormat);        
                if (cv::imwrite(filename, image)) {
                    std::cout << "0256x0256." + 
                        std::to_string(channels) + "." + dtype.name + "." + imgFormat << std::endl;
                }
            }
        }
    }
    lst_file.close();
    std::cout << "Все изображения успешно созданы и сохранены." << std::endl;
}

std::string check_image(const fs::path& image_path) {
    const cv::Mat image = cv::imread(image_path.string(), cv::IMREAD_UNCHANGED);

    if (image.empty()) {
        std::cerr << image_path << "\tbad, could not open image" << std::endl;
        return "bad, could not open image";
    }

    const std::string actual = strid_from_mat(image);
    std::cout << image_path << ' ' << actual << ' ' << image_path << std::endl;

    const std::regex pattern(R"((\d{4}x\d{4}\.\d+\.\w+))");
    std::smatch match;

    const std::string filename = image_path.filename().string();
    if (std::regex_search(filename, match, pattern)) {
        const std::string extracted = match.str(1);
        if (extracted == actual) {
            std::cout << image_path << "\tgood" << std::endl;
            return "good";
        } else {
            std::cout << image_path << "\tbad, should be " << extracted << std::endl;
            return "bad, should be " + extracted;
        }
    } else {
        std::cerr << image_path << "\tbad, pattern not found in filename" << std::endl;
        return "bad, pattern not found in filename";
    }
} 

int main(int argc, const char** argv) {
    const fs::path img_dir = BASE_DIR / "images";
    try {
        if (!fs::exists(img_dir)) {
            if (fs::create_directory(img_dir)) {
                std::cout << "Directory created: " << img_dir << '\n';
                gen_data(img_dir / "task01.lst");
            } else {
                std::cerr << "Failed to create directory: " << img_dir << '\n';
            }
        } else if (fs::is_directory(img_dir) && fs::is_empty(img_dir)) {
            std::cout << "Directory is empty: " << img_dir << '\n';
            gen_data(img_dir);
        } else {
            std::cout << "Directory already exists and is not empty: " << img_dir << '\n';
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }

    fs::path lst_file = img_dir / "task01.lst";

    if (argc == 1) {
        lst_file = img_dir / "task01.lst";
    } else {
        lst_file = argv[1];
    }

    const std::vector<fs::path> files = get_list_of_file_paths(lst_file);
    for (const auto& entry: files) {
        std::string res = check_image(entry);
        std::cout << res;
    }
    return 0;
}