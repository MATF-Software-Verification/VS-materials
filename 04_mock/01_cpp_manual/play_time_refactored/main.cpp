#include "mock_clock.h"
#include "play_time.h"
#include "system_clock.h"
#include <iostream>
using namespace std;

int main() {
    play_time game(make_shared<system_clock>());

    game.start_session();
    cout << "Let's play for a while!" << endl;

    sleep(12);

    cout << "It's enough...for now..." << endl;
    game.stop_session();

    cout << game.played_time() << endl;
    return 0;
}
