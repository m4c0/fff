module fff;
import silog;

using namespace fff;

namespace {
  class cf_timer : public timer_t {
  public:
    cf_timer() {}
    virtual ~cf_timer() {}
  };
}

timer_t * timer::create(unsigned ms) {
  return new cf_timer {};
}
