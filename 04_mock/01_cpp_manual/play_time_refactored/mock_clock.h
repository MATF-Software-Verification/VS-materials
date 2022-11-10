#ifndef MOCK_CLOCK_H
#define MOCK_CLOCK_H

#include "second_clock.h"

class mock_clock : public second_clock
{
public:
    mock_clock(pt::ptime current_time);
    virtual ~mock_clock() =default;
    void set(pt::ptime new_current_time);

private:
    pt::ptime get_current_time()  const;
    pt::ptime  current_time;
};

#endif // MOCK_CLOCK_H
