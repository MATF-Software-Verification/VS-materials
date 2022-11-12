#ifndef SECOND_CLOCK_H
#define SECOND_CLOCK_H

#include <boost/date_time/posix_time/posix_time.hpp>
namespace pt = boost::posix_time;

class second_clock {
 public:
	pt::ptime operator () () const;

	// forbids making copies of second_clocks
	second_clock(second_clock const &) = delete;
	second_clock & operator =(second_clock const &sc) = delete;

	virtual ~ second_clock() = default;
 protected:
	second_clock() = default;
 private:
	// called by operator (), child classes must implement this function 
	virtual pt::ptime get_current_time() const = 0;
};

#endif				// SECOND_CLOCK_H
