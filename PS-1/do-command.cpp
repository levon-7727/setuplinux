#include <iostream>
#include <chrono>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

void do_command(char** argv) {
    auto start = std::chrono::high_resolution_clock::now();

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Failed to fork process\n";
        return;
    }

    if (pid == 0) {
        execvp(argv[0], argv);
        std::cerr << "Failed to execute command\n";
        std::exit(1);
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            std::cerr << "Error waiting for child process\n";
            return;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double>(end - start).count();

        int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
        std::cout << "\nCommand completed with " << exit_code 
                  << " exit code and took " << duration << " seconds.\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [args...]\n";
        return 1;
    }

    do_command(&argv[1]);

    return 0;
}

