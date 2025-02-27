#include <iostream>
#include <filesystem>
#include <vector>
#include <opencv2/core.hpp>
#include "semcv/semcv.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
    os << '[';
    for (int i = 0; i < vec.size() - 1; i++) {
        os << vec[i] << ", ";
    }
    os << vec[vec.size() - 1] << ']';
}

namespace fs = std::filesystem;

int main(int argc, const char** argv) {
    fs::path images_dir = BASE_DIR / "images";
    fs::path lst_file;

    if (argc == 1) {
        lst_file = images_dir / "task01.lst";
    } else {
        lst_file = argv[1];
    }
    std::vector<fs::path> files = get_list_of_file_paths(lst_file);
    for (const auto& entry : files) {
        std::cout << entry << std::endl;
    }

    return 0;
}