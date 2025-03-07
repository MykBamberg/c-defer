#ifndef defer

#if defined(__GNUC__) && !defined(__clang__)

#define __DEFER__(F, V) \
  [[gnu::always_inline]] auto inline void F(int*); \
  [[gnu::cleanup(F)]] int V; \
  auto void F(int*)

#define defer __DEFER(__COUNTER__)
#define __DEFER(N) __DEFER_(N)
#define __DEFER_(N) __DEFER__(__DEFER_FUNCTION_ ## N, __DEFER_VARIABLE_ ## N)

#else

#error "This defer implementation only works using GCC"
#define defer

#endif
#endif
