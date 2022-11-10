#include "play_time.h"

play_time::play_time(std::shared_ptr<second_clock> cclock)
    :clock(cclock)
{}

void play_time::start_session(){
    session_start = (*clock)();
}

void play_time::stop_session(){
    auto const  current_time = (*clock)();
    total_time += current_time- session_start;
}

pt::time_duration play_time::played_time() const{
    return total_time;
}
