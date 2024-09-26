module;
#pragma leco add_library X11
#include <errno.h>
#include <signal.h>
#include <time.h>

module fff;
import silog;

using namespace fff;

namespace {
  class cf_timer : public timer_t {
  public:
    explicit cf_timer() {}
    virtual ~cf_timer() {}
  };
} // namespace

timer_t * timer::create(unsigned ms) {
  constexpr const auto timer_cb = [](sigval) {
    auto self = static_cast<timer *>(info);
    self->m_fn();
  };

  sigevent sevp {};
  sevp.sigev_notify = SIGEV_THREAD;
  sevp.sigev_notify_function = timer_cb;

  timer_t timer {};
  if (0 != timer_create(CLOCK_REALTIME, &sevp, &timer)) {
    silog::log(silog::error, "Failed to create timer: %s", strerror(errno));
  }

  static constexpr const auto ms_per_tick = 1000 / 20;
  static constexpr const auto us_per_tick = ms_per_tick * 1000;
  static constexpr const auto ns_per_tick = us_per_tick * 1000;

  itimerspec its {};
  its.it_interval.tv_nsec = ns_per_tick;
  its.it_value = its.it_interval;
  timer_settime(timer, 0, &its, nullptr);

#error TODO: implement timer
  return new cf_timer {};
}
