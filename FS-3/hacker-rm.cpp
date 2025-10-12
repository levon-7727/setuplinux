#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file-to-erase>\n";
        return EXIT_FAILURE;
    }

    const char* path = argv[1];
    struct stat st;
    if (stat(path, &st) == -1) {
        std::cerr << "stat failed: " << strerror(errno) << "\n";
        return EXIT_FAILURE;
    }

    if (!S_ISREG(st.st_mode)) {
        std::cerr << "not a regular file\n";
        return EXIT_FAILURE;
    }

    off_t size = st.st_size;
    int fd = open(path, O_WRONLY);
    if (fd == -1) {
        std::cerr << "open failed: " << strerror(errno) << "\n";
        return EXIT_FAILURE;
    }

    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        std::cerr << "lseek failed: " << strerror(errno) << "\n";
        close(fd);
        return EXIT_FAILURE;
    }

    const size_t CHUNK = 65536;
    char *zeros = new(std::nothrow) char[CHUNK];
    if (!zeros) {
        std::cerr << "allocation failed\n";
        close(fd);
        return EXIT_FAILURE;
    }
    memset(zeros, 0, CHUNK);

    off_t remaining = size;
    while (remaining > 0) {
        ssize_t to_write = (remaining > (off_t)CHUNK) ? CHUNK : (ssize_t)remaining;
        ssize_t w = write(fd, zeros, to_write);
        if (w == -1) {
            std::cerr << "write failed: " << strerror(errno) << "\n";
            delete[] zeros;
            close(fd);
            return EXIT_FAILURE;
        }
        remaining -= w;
    }

    if (fsync(fd) == -1) {
        std::cerr << "fsync failed: " << strerror(errno) << "\n";
        delete[] zeros;
        close(fd);
        return EXIT_FAILURE;
    }

    delete[] zeros;
    if (close(fd) == -1) {
        std::cerr << "close failed: " << strerror(errno) << "\n";
        return EXIT_FAILURE;
    }

    if (unlink(path) == -1) {
        std::cerr << "unlink failed: " << strerror(errno) << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

