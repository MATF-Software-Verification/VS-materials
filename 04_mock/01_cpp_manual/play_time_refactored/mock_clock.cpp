#include "mock_clock.h"

mock_clock::mock_clock(pt::ptime current)
 : current_time(current)
{
}

pt::ptime mock_clock::get_current_time()const
{
	return current_time;
}

void mock_clock::set(pt::ptime new_current)
{
	current_time = new_current;
}
