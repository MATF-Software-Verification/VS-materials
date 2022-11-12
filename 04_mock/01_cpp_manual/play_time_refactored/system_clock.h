#ifndef SYSTEM_CLOCK_H
#define SYSTEM_CLOCK_H

#include "second_clock.h"

class system_clock:public second_clock {
 public:
	system_clock() = default;
	virtual ~ system_clock() override = default;

 private:
	pt::ptime get_current_time() const override final;
};

#endif				// SYSTEM_CLOCK_H
