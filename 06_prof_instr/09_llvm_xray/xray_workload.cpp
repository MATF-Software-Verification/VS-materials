#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

[[clang::xray_always_instrument]] static long busy_work(int rounds) {
    long value = 0;
    for (int i = 0; i < rounds; i++) {
        value += (i * 17) % 31;
    }
    return value;
}

[[clang::xray_always_instrument]] static long sort_work() {
    std::vector<int> values(2000);
    std::iota(values.rbegin(), values.rend(), 1);
    std::sort(values.begin(), values.end());
    return values[values.size() / 2];
}

[[clang::xray_always_instrument]] static void wait_work() {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

[[clang::xray_always_instrument]] static long handle_request(int id) {
    long result = busy_work(20000 + id * 100);
    result += sort_work();
    if (id % 5 == 0) {
        wait_work();
    }
    return result;
}

int main() {
    long total = 0;
    for (int i = 0; i < 30; i++) {
        total += handle_request(i);
    }

    std::cout << "total=" << total << "\n";
    return 0;
}
