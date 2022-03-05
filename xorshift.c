#include "type.h"
#include "xorshift.h"

u32 xorshift(u32 state)
{
  u32 x = state;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

void xorshift_add_entropy(xorshift_state_t * state, u32 e)
{
  state->e += e;
  state->e = xorshift(state->e);
}

#define RAND_MAX 0xffffffff

u32 xorshift_rand(xorshift_state_t * state, u32 pot_mod)
{
  state->a = xorshift(state->a);
  state->a += state->e;
  do {
    state->a = xorshift(state->a);
  } while (state->a >= (RAND_MAX - (RAND_MAX & (pot_mod - 1))));
  return state->a & (pot_mod - 1);
}
