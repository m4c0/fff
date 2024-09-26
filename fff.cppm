export module fff;
import hai;

namespace fff {
  struct timer_t {
    virtual ~timer_t() {}
  };

  export class timer {
    hai::fn<void> m_fn {};
    hai::uptr<timer_t> m_ptr {};

    timer_t * create(unsigned ms);

  public:
    constexpr timer() = default;
    timer(unsigned ms, hai::fn<void> fn) : m_fn { fn }, m_ptr { create(ms) } {}
  };
}

#if LECO_TARGET_APPLE
#pragma leco add_impl apple.cpp
#endif
