#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source-file> <destination-file>\n";
        return EXIT_FAILURE;
    }

    const char* src = argv[1];
    const char* dst = argv[2];

    std::ifstream src_file(src, std::ios::binary);
    if (!src_file) {
        std::cerr << "Error opening source file '" << src << "'\n";
        return EXIT_FAILURE;
    }

    std::ofstream dst_file(dst, std::ios::binary | std::ios::trunc);
    if (!dst_file) {
        std::cerr << "Error opening destination file '" << dst << "'\n";
        return EXIT_FAILURE;
    }

    char buffer[4096];
    while (src_file.read(buffer, sizeof(buffer)) || src_file.gcount() > 0) {
        dst_file.write(buffer, src_file.gcount());
        if (!dst_file) {
            std::cerr << "Write error\n";
            return EXIT_FAILURE;
        }
    }

    if (!src_file.eof()) {
        std::cerr << "Read error\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

