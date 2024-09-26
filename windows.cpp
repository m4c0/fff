module;
#include <windows.h>

module fff;
import silog;

using namespace fff;

namespace {
  class cf_timer : public timer_t {
    HANDLE m_ref;

  public:
    explicit cf_timer(HANDLE r) : m_ref { r } {}
    virtual ~cf_timer() { DeleteTimerQueueEx(m_ref, nullptr); }
  };
} // namespace

timer_t * timer::create(unsigned ms) {
  constexpr const auto timer_cb = [](void * info, BOOLEAN) {
    auto self = static_cast<timer *>(info);
    self->m_fn();
  };

  HANDLE t;

  auto tq = CreateTimerQueue();
  CreateTimerQueueTimer(&t, tq, timer_cb, this, ms, ms, 0);
  return new cf_timer { tq };
}
