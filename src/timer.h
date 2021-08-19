#ifndef TASTE_TIMER_H
#define TASTE_TIMER_H

#include <chrono>
#include <thread>

namespace taste {
class Timer final {
public:
  Timer() = default;

  template <typename T>
  void run(std::chrono::milliseconds interval, T callback) {
    auto start = std::chrono::steady_clock::now();
    while (true) {
      using namespace std::chrono_literals;
      auto jitter = std::chrono::steady_clock::now() - start;
      auto diff = interval - jitter;
      if (diff > 0ms) {
        std::this_thread::sleep_for(diff);
      }
      callback();

      start = std::chrono::steady_clock::now();
    }
  }
};
} // namespace taste

#endif
