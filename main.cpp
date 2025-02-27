#include <iostream>
#include <opencv2/core.hpp>

#include "semcv/semcv.hpp"

namespace fs = std::filesystem;
fs::path BASE_DIR = fs::path(__FILE__).parent_path();
fs::path images_dir = BASE_DIR / "images";

int main(int argc, const char** argv) {
    std::cout << images_dir << std::endl;
    return 0;
}