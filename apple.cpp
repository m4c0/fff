module;
#include <CoreFoundation/CoreFoundation.h>

module fff;
import silog;

using namespace fff;

namespace {
  class cf_timer : public timer_t {
    CFRunLoopTimerRef m_ref;

  public:
    explicit cf_timer(CFRunLoopTimerRef r) : m_ref { r } {}
    virtual ~cf_timer() { CFRelease(m_ref); }
  };
} // namespace

timer_t * timer::create(unsigned ms) {
  CFAbsoluteTime secs = ms / 1000.0f;

  CFRunLoopTimerContext ctx { .info = this };

  constexpr const auto timer_cb = [](CFRunLoopTimerRef ref, void * info) {
    auto self = static_cast<timer *>(info);
    self->m_fn();
  };

  auto fire_date = CFAbsoluteTimeGetCurrent() + secs;

  auto t = CFRunLoopTimerCreate(nullptr, fire_date, secs, 0, 0, timer_cb, &ctx);
  CFRunLoopAddTimer(CFRunLoopGetMain(), t, kCFRunLoopCommonModes);
  // Setup notifications for enter bg
  return new cf_timer { t };
}
