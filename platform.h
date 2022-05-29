#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>

class Platform
{
public:
    Platform(const int sz = 10) : size(sz) {}

    int getSize() const noexcept { return size; }
    friend std::ostream& operator<<(std::ostream& os, const Platform& p);

private:
    int size;
};

#endif // PLATFORM_H
