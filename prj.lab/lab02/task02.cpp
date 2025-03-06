#include <iostream>
#include <opencv2/opencv.hpp>
#include <tuple>
#include <array>
#include <filesystem>
#include "semcv/semcv.hpp"

namespace fs = std::filesystem;

int main(int argc, const char** argv) {
    std::vector<std::tuple<int, int, int>> brightnesses = {
        {0, 127, 255},
        {20, 127, 235},
        {55, 127, 200},
        {90, 127, 165}
    };

    std::array<int, 4> stds = {0, 3, 7, 15}; // first row of image doesn't have noise

    cv::Mat res_collage;
    std::vector<cv::Mat> collage_of_rows;
    for (const auto& [back, inner, circle] : brightnesses) {
        std::vector<cv::Mat> collage_rowmats;
        cv::Mat current_row_mat;
        for (const auto& std : stds) {
            cv::Mat img = gen_tgtimg00(back, inner, circle);
            cv::Mat noise_img = add_noise_gau(img, std);
            collage_rowmats.push_back(noise_img);
        }
        cv::vconcat(collage_rowmats, current_row_mat);
        collage_of_rows.push_back(current_row_mat);
    }
    cv::hconcat(collage_of_rows, res_collage);

    fs::path save_path = resolve_result_dir(__FILE__, "res02.png");
    cv::imwrite(save_path, res_collage);
    return 0;
}
