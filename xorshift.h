#include "type.h"

typedef struct xorshift_state {
  u32 a;
  u32 e;
} xorshift_state_t;

u32 xorshift(u32 state);

void xorshift_add_entropy(xorshift_state_t * state, u32 e);

u32 xorshift_rand(xorshift_state_t * state, u32 mod);
