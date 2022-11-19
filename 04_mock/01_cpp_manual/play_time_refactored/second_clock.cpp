#include "second_clock.h"

pt::ptime second_clock::operator()() const { return get_current_time(); }
