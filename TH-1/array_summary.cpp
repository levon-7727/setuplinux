#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <chrono>

struct ThreadData {
    const std::vector<int>* arr;
    size_t start;
    size_t end;
    long long partial_sum;
};

void* sum_array_part(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long sum = 0;
    for (size_t i = data->start; i < data->end; ++i) {
        sum += (*data->arr)[i];
    }
    data->partial_sum = sum;
    pthread_exit(nullptr);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <N> <M>\n";
        return 1;
    }

    size_t N = std::stoull(argv[1]);
    size_t M = std::stoull(argv[2]);

    if (N < 2 || M < 1) {
        std::cerr << "Error: N must be > 1 and M >= 1\n";
        return 1;
    }

    std::vector<int> arr(N);
    std::srand((unsigned)std::time(nullptr));
    for (size_t i = 0; i < N; ++i)
        arr[i] = std::rand() % 100;

    auto start_single = std::chrono::high_resolution_clock::now();
    long long sum_single = 0;
    for (size_t i = 0; i < N; ++i)
        sum_single += arr[i];
    auto end_single = std::chrono::high_resolution_clock::now();
    auto duration_single = std::chrono::duration<double>(end_single - start_single).count();

    std::vector<pthread_t> threads(M);
    std::vector<ThreadData> thread_data(M);

    size_t chunk_size = N / M;
    auto start_multi = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < M; ++i) {
        thread_data[i].arr = &arr;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == M - 1) ? N : (i + 1) * chunk_size;
        thread_data[i].partial_sum = 0;
        pthread_create(&threads[i], nullptr, sum_array_part, &thread_data[i]);
    }

    long long sum_multi = 0;
    for (size_t i = 0; i < M; ++i) {
        pthread_join(threads[i], nullptr);
        sum_multi += thread_data[i].partial_sum;
    }

    auto end_multi = std::chrono::high_resolution_clock::now();
    auto duration_multi = std::chrono::duration<double>(end_multi - start_multi).count();

    std::cout << "Time spent without threads: " << duration_single << " seconds\n";
    std::cout << "Time spent with " << M << " threads: " << duration_multi << " seconds\n";

    if (sum_single != sum_multi) {
        std::cerr << "Error: sums do not match!\n";
        return 1;
    }

    return 0;
}

