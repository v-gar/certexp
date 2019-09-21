#include "utils.hpp"

using std::tm;
using std::time_t;

signed int get_expire_day_difference(tm *expire_date)
{
    time_t now = std::time(nullptr);
    time_t expire = std::mktime(expire_date);

    auto diff = expire - now;

    constexpr float SECONDS_PER_DAY = 24 * 60 * 60;

    return (signed int) std::floor(diff / SECONDS_PER_DAY);
}

