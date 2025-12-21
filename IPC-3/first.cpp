#include "shared_array.h"
#include <iostream>
#include <unistd.h>

int main()
{
    shared_array arr("demo_array", 5);

    int counter = 0;

    while (true)
    {
        arr.lock();

        for (int i = 0; i < 5; ++i)
            arr[i] = counter + i;

        std::cout << "[FIRST] ";
        for (int i = 0; i < 5; ++i)
            std::cout << arr[i] << " ";
        std::cout << std::endl;

        arr.unlock();

        counter++;
        sleep(1);
    }
}
