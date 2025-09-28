#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file>\n";
        return 1;
    }

    const char* path = argv[1];
    std::ifstream file(path, std::ios::binary);

    if (!file) {
        std::cerr << "Error opening '" << path << "'\n";
        return 1;
    }

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        std::cout.write(buffer, file.gcount());
        if (!std::cout) {
            std::cerr << "Write error\n";
            return 1;
        }
    }

    return 0;
}

