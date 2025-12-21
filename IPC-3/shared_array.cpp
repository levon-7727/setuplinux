#include "shared_array.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdexcept>

shared_array::shared_array(const std::string& n, size_t s)
    : name(n), size(s), shm_fd(-1), data(nullptr), sem(nullptr), owner(false)
{
    if (size < 1 || size > 1'000'000'000)
        throw std::invalid_argument("invalid array size");

    std::string shm_name = "/" + name;
    std::string sem_name = "/" + name + "_sem";

    shm_fd = shm_open(shm_name.c_str(), O_CREAT | O_EXCL | O_RDWR, 0666);
    if (shm_fd != -1)
    {
        owner = true;
        if (ftruncate(shm_fd, size * sizeof(int)) == -1)
        {
            shm_unlink(shm_name.c_str());
            throw std::runtime_error("ftruncate failed");
        }
    }
    else
    {
        shm_fd = shm_open(shm_name.c_str(), O_RDWR, 0666);
        if (shm_fd == -1)
            throw std::runtime_error("shm_open failed");

        struct stat st;
        if (fstat(shm_fd, &st) == -1)
            throw std::runtime_error("fstat failed");

        if (st.st_size != (off_t)(size * sizeof(int)))
            throw std::runtime_error("shared memory size mismatch");
    }

    data = static_cast<int*>(
        mmap(nullptr, size * sizeof(int),
             PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0)
    );

    if (data == MAP_FAILED)
    {
        if (owner)
            shm_unlink(shm_name.c_str());
        throw std::runtime_error("mmap failed");
    }

    sem = sem_open(sem_name.c_str(), O_CREAT, 0666, 1);
    if (sem == SEM_FAILED)
        throw std::runtime_error("sem_open failed");
}


shared_array::shared_array(shared_array&& other) noexcept
    : name(std::move(other.name)),
      size(other.size),
      shm_fd(other.shm_fd),
      data(other.data),
      sem(other.sem),
      owner(other.owner)
{
    other.shm_fd = -1;
    other.data = nullptr;
    other.sem = nullptr;
    other.size = 0;
    other.owner = false;
}

shared_array::~shared_array()
{
    if (data)
        munmap(data, size * sizeof(int));
    if (shm_fd != -1)
        close(shm_fd);
    if (sem)
        sem_close(sem);
}

int& shared_array::operator[](size_t index)
{
    if (index >= size)
        throw std::out_of_range("index out of range");
    return data[index];
}

void shared_array::lock()
{
    sem_wait(sem);
}

void shared_array::unlock()
{
    sem_post(sem);
}

void shared_array::unlink(const std::string& name)
{
    shm_unlink(("/" + name).c_str());
    sem_unlink(("/" + name + "_sem").c_str());
}
