#include "shared_array.h"
#include <iostream>
#include <unistd.h>

int main()
{
    shared_array arr("demo_array", 5);

    while (true)
    {
        arr.lock();

        std::cout << "[SECOND] ";
        for (int i = 0; i < 5; ++i)
        {
            arr[i] += 10;
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

        arr.unlock();

        sleep(2);
    }
}
