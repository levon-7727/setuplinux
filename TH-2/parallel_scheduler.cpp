#include "parallel_scheduler.h"

parallel_scheduler::parallel_scheduler(size_t capacity) : stop(false) {
    for (size_t i = 0; i < capacity; i++) {
        threads.emplace_back(&parallel_scheduler::worker, this);
    }
}

parallel_scheduler::~parallel_scheduler() {
    stop = true;
    cv.notify_all();
    for (auto &t : threads) t.join();
}

void parallel_scheduler::worker() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(mtx);

            cv.wait(lock, [&]() { 
                return stop || !tasks.empty(); 
            });

            if (stop && tasks.empty()) return;

            task = std::move(tasks.front());
            tasks.pop();
        }

        task();
    }
}
