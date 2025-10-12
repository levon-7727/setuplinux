#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input-file>\n";
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        std::perror("Error opening file");
        return EXIT_FAILURE;
    }

    if (dup2(fd, STDIN_FILENO) == -1) {
        std::perror("Error redirecting stdin");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);

    std::string input;
    if (!(std::cin >> input)) {
        std::cerr << "Failed to read input.\n";
        return EXIT_FAILURE;
    }

    std::string reversed(input.rbegin(), input.rend());
    std::cout << reversed << std::endl;

    return EXIT_SUCCESS;
}

