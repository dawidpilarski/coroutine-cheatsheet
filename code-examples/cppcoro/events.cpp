

#include <cppcoro/single_consumer_event.hpp>
#include <cppcoro/task.hpp>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/when_all_ready.hpp>
#include <thread>
#include <experimental/coroutine>
#include <iostream>
#include <chrono>

using namespace cppcoro;
using namespace std;
using namespace std::literals;

struct scheduler {
  struct promise_type;
  using this_coro_t = std::experimental::coroutine_handle<promise_type>;

  scheduler(this_coro_t this_coro) : coro(this_coro) {}

  scheduler(const scheduler& rhs) = default;

  struct promise_type {
    scheduler get_return_object() { return this_coro_t::from_promise(*this); }

    std::experimental::suspend_never initial_suspend() { return {}; }

    std::experimental::suspend_always final_suspend() { return {}; }

    void unhandled_exception() { throw; }

    void return_void() {}
  };

  this_coro_t coro;
};

scheduler start_task(task<> task) {
  co_await task;
}

template <typename... Task>
void sched(Task&&... tasks) {
  (start_task(std::move(tasks)),...);
}

void test() {
  single_consumer_event ev_ping;
  single_consumer_event ev_pong;
  sched(
    [&]() -> cppcoro::task<> {
      while (true) {
        co_await ev_ping;
        std::cout << "ping" << std::endl;
        ev_ping.reset();
        ev_pong.set();
      }
    }(),
    [&]() -> cppcoro::task<> {
      while (true) {
        ev_ping.set();
        co_await ev_pong;
        ev_pong.reset();
        std::cout << "pong" << std::endl;
        std::this_thread::sleep_for(1000ms);
      }
    }());
}


int main() {
  test();
}

