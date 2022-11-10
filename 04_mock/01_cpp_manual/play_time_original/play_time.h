#ifndef PLAY_TIME_H
#define PLAY_TIME_H

#include <boost/date_time/posix_time/posix_time.hpp>
namespace pt =boost::posix_time;
class play_time
{
public:
    play_time();
    void start_session();
    void stop_session();
    pt::time_duration played_time() const;

private:
    pt::ptime session_start;
    pt::time_duration total_time;
};

#endif // PLAY_TIME_H
