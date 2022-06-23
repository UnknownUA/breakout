#include "platform.h"

//hotfix
std::ostream& operator<<(std::ostream& os, const Platform& p)
{
    for (int i = 0; i < p.size; ++ i)
        os << char (223);
    return os;
}

