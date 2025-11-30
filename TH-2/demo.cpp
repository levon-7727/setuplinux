#include <iostream>
#include "parallel_scheduler.h"
#include <unistd.h>

void do_work(int n) {
    std::cout << "Task " << n << " started\n";
    sleep(1); 
    std::cout << "Task " << n << " finished\n";
}

int main() {
    parallel_scheduler ps(3); 

    for (int i = 1; i <= 10; i++) {
        ps.run(do_work, i);
    }

    sleep(2); 
    return 0;
}
