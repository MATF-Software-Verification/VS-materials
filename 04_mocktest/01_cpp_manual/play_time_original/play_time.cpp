#include "play_time.h"

play_time::play_time() {}

void play_time::start_session() {
    session_start = pt::second_clock::local_time();
}

void play_time::stop_session() {
    auto const current_time = pt::second_clock::local_time();
    total_time += current_time - session_start;
}

pt::time_duration play_time::played_time() const { return total_time; }
