#include "system_clock.h"


pt::ptime system_clock::get_current_time() const{
    return pt::second_clock::local_time();
}
