#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source-file> <destination-file>\n";
        return EXIT_FAILURE;
    }

    const char* src_path = argv[1];
    const char* dst_path = argv[2];

    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);
        return EXIT_FAILURE;
    }

    off_t offset = 0;
    off_t end;
    struct stat st;
    if (fstat(src_fd, &st) == -1) {
        perror("fstat failed");
        close(src_fd);
        close(dst_fd);
        return EXIT_FAILURE;
    }
    end = st.st_size;

    ssize_t total_bytes = 0;
    ssize_t data_bytes = 0;
    ssize_t hole_bytes = 0;
    const size_t buf_size = 4096;
    char buffer[buf_size];

    while (offset < end) {
        off_t data_off = lseek(src_fd, offset, SEEK_DATA);
        if (data_off == -1) data_off = end; 
        off_t hole_off = lseek(src_fd, offset, SEEK_HOLE);
        if (hole_off == -1) hole_off = end;

        if (data_off < hole_off) {
            hole_bytes += data_off - offset;
            offset = data_off;
        }

        ssize_t to_read = hole_off - offset;
        ssize_t r;
        while (to_read > 0) {
            ssize_t chunk = (to_read < buf_size) ? to_read : buf_size;
            r = read(src_fd, buffer, chunk);
            if (r <= 0) break;
            ssize_t w = write(dst_fd, buffer, r);
            if (w != r) {
                perror("write failed");
                close(src_fd);
                close(dst_fd);
                return EXIT_FAILURE;
            }
            data_bytes += r;
            to_read -= r;
        }
        offset = hole_off;
    }

    total_bytes = data_bytes + hole_bytes;
    std::cout << "Successfully copied " << total_bytes
              << " bytes (data: " << data_bytes
              << ", hole: " << hole_bytes << ").\n";

    close(src_fd);
    close(dst_fd);
    return EXIT_SUCCESS;
}

