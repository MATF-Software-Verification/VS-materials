#ifndef PLAY_TIME_H
#define PLAY_TIME_H
#include  "second_clock.h"

#include <boost/date_time/posix_time/posix_time.hpp>
namespace pt =boost::posix_time;

class play_time
{
public:
		//use given clock to get the current time
		// shared_ptr is there to ensure clock is kept alive
    play_time(std::shared_ptr<second_clock> cclock );
    
    void start_session();
    void stop_session();
    pt::time_duration played_time() const;

private:
    std::shared_ptr<second_clock> clock;
    pt::ptime session_start;
    pt::time_duration total_time;
};

#endif // PLAY_TIME_H
