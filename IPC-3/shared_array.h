#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <string>
#include <semaphore.h>
#include <cstddef>

class shared_array
{
private:
    std::string name;
    size_t      size;
    int         shm_fd;
    int*        data;
    sem_t*      sem;
    bool        owner;

public:
    shared_array(const std::string& name, size_t size);

    shared_array(const shared_array&) = delete;
    shared_array& operator=(const shared_array&) = delete;

    shared_array(shared_array&& other) noexcept;

    ~shared_array();

    int& operator[](size_t index);

    void lock();
    void unlock();

    static void unlink(const std::string& name);
};

#endif
