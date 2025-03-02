#include <iostream>
#include <vector>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include "semcv/semcv.hpp"

cv::Mat generate_1c_8bpp_image(int width = 768, int height = 30, int stripe_width = 3) {
    int stripes_count = width / stripe_width;
    if (stripes_count > 256 || width % stripe_width != 0) {
        throw std::invalid_argument("invalid width or stripe_width");
    }

    cv::Mat img = cv::Mat(height, width, CV_8UC1);
    if (img.empty()) {
        throw std::runtime_error("Failed to create image");
    }


    for (int i = 0; i < stripes_count; i++) {
        cv::Rect stripe(stripe_width * i, 0, stripe_width, height);
        img(stripe).setTo(i);
    }
    return img;
}

cv::Mat apply_gamma_correction(const cv::Mat& img, double gamma) {
    CV_Assert(gamma > 0);

    cv::Mat result;
    cv::Mat lut(1, 256, CV_8U); 

    for (int i = 0; i < 256; i++) {
        int new_value = std::round(std::pow(i / 255.0, gamma) * 255.0);
        lut.at<uchar>(0, i) = cv::saturate_cast<uchar>(new_value);
    }
    cv::LUT(img, lut, result);
    return result;
}


int main(int argc, const char** argv) {
    std::vector<cv::Mat> images;

    for (float gamma = 1.8; gamma <= 2.6 + 0.1; gamma += 0.2) {
        cv::Mat generated = generate_1c_8bpp_image();
        cv::Mat res = apply_gamma_correction(generated, gamma);
        images.push_back(res);
    }

    cv::Mat collage;
    cv::vconcat(images, collage);

    cv::imwrite("collage.png", collage);
    cv::imshow("Gamma Collage", collage);
    cv::waitKey(0);

    return 0;
}