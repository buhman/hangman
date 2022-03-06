#include "type.h"
#include "base.h"
#include "register.h"

#include "keyboard.h"

#ifdef ROMANIAN
static const char keyboard[3][KEYBOARD_COLS] = {
  {_Q_, _W_, _E_, _R_, _T_, _Y_, _U_, _I_, _O_, _P_      , _A_BREVE_, _I_CIRCUMFLEX_, _A_CIRCUMFLEX_},
  {_A_, _S_, _D_, _F_, _G_, _H_, _J_, _K_, _L_, _S_COMMA_, _T_COMMA_,             -1,             -1},
  {_Z_, _X_, _C_, _V_, _B_, _N_, _M_,  -1,  -1,        -1,        -1,             -1,             -1},
};

const int keyboard_max_x[3] = {
  [0] = 12,
  [1] = 10,
  [2] = 6,
};
#else
static const char keyboard[3][KEYBOARD_COLS] = {
  {_Q_, _W_, _E_, _R_, _T_, _Y_, _U_, _I_, _O_, _P_},
  {_A_, _S_, _D_, _F_, _G_, _H_, _J_, _K_, _L_,  -1},
  {_Z_, _X_, _C_, _V_, _B_, _N_, _M_,  -1,  -1,  -1},
};

const int keyboard_max_x[3] = {
  [0] = 9,
  [1] = 8,
  [2] = 6,
};
#endif

void keyboard_draw(u32 col, u32 row)
{
  int start = 16 * 32 + 10;

  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < KEYBOARD_COLS; x++) {
      char c = keyboard[y][x];
      c = c == -1 ? 0 : c;

      char palette = (row == y && col == x);

      *(reg16 *)(VRAM
                + SCREEN_BASE_BLOCK(31)
                + (start * 2)
                + (((y * 32) + x) * 2)
                )
        = SCREEN_TEXT__PALETTE(palette) | (c + 16);
    }
  }
}

int keyboard_get_letter(int x, int y)
{
  return keyboard[y][x];
}
