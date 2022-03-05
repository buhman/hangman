#include "base.h"
#include "register.h"
#include "type.h"
#include "copy.h"
#include "nib.h"
#include "glyph.h"
#include "keyboard.h"
#include "hang.h"

typedef struct keyboard {
  s8 x;
  s8 y;
} keyboard_t;


typedef struct count_flop {
  s8 count;
  u8 flop;
} count_flop_t;

typedef struct input {
  count_flop_t left;
  count_flop_t right;
  count_flop_t up;
  count_flop_t down;
  count_flop_t a;
  count_flop_t start;
} input_t;

typedef struct state {
  keyboard_t keyboard;
  input_t input;
  u32 guessed;
  u8 hang;
  int word_ix;
} state_t;

static state_t state = { 0 };

static inline void key_input_count(count_flop_t * key, unsigned int input, unsigned int mask)
{
  if (input & mask) {
    if (key->count < 2)
      key->count += 1;
  } else {
    if (key->count > 0)
      key->count -= 1;
    if (key->count == 0)
      key->flop = 0;
  }
}

static inline int key_flopped(count_flop_t * key)
{
  if (key->count == 2 && key->flop == 0) {
    key->flop = 1;
    return 1;
  } else {
    return 0;
  }
}

static const int keyboard_max_x[3] = {
  [0] = 9,
  [1] = 8,
  [2] = 6,
};

static inline void next_word(void)
{
  state.guessed = (1 << 0 | 1 << 4 | 1 << 8 | 1 << 14 | 1 << 20);
  state.hang = HANG__LAST - 1;
  state.word_ix += 1;
}

static inline void keyboard_input(void)
{
  int letter = keyboard_get_letter(state.keyboard.x, state.keyboard.y);
  if (letter < 0 || letter > 31) {
    // do nothing; invalid letter
  } else {
    if ((state.guessed & (1 << letter)) == 0) {
      state.guessed |= (1 << letter);

      if (!hang_letter_in_word(state.word_ix, letter))
        state.hang -= 1;
    }
  }
}

void _user_isr(void)
{
  *(reg16 *)(IO_REG + IME) = 0;

  u32 ireq = *(reg16 *)(IO_REG + IF);

  // hackety hack
  /*
  if (state.hang == 0 && state.guessed == 0)
    next_word();
  */

  /* key input */

  u32 key_input = ~(*(reg16 *)(IO_REG + KEY_INPUT));

  key_input_count(&state.input.left, key_input, KEYCNT__INPUT_LEFT);
  key_input_count(&state.input.right, key_input, KEYCNT__INPUT_RIGHT);
  key_input_count(&state.input.up, key_input, KEYCNT__INPUT_UP);
  key_input_count(&state.input.down, key_input, KEYCNT__INPUT_DOWN);
  key_input_count(&state.input.a, key_input, KEYCNT__INPUT_A);
  key_input_count(&state.input.start, key_input, KEYCNT__INPUT_ST);

  if (key_flopped(&state.input.up)) {
    if (state.keyboard.y == 0)
      state.keyboard.y = 2;
    else
      state.keyboard.y -= 1;
  }
  if (key_flopped(&state.input.down)) {
    if (state.keyboard.y == 2)
      state.keyboard.y = 0;
    else
      state.keyboard.y += 1;
  }
  if (state.keyboard.x > keyboard_max_x[state.keyboard.y])
    state.keyboard.x = keyboard_max_x[state.keyboard.y];


  if (key_flopped(&state.input.left)) {
    if (state.keyboard.x == 0)
      state.keyboard.x = keyboard_max_x[state.keyboard.y];
    else
      state.keyboard.x -= 1;
  }
  if (key_flopped(&state.input.right)) {
    if (state.keyboard.x == keyboard_max_x[state.keyboard.y])
      state.keyboard.x = 0;
    else
      state.keyboard.x += 1;
  }
  if (key_flopped(&state.input.a)) {
    if (hang_word_complete(state.word_ix, state.guessed) || state.hang <= HANG_DEAD) {
      // do nothing
    } else {
      keyboard_input();
    }
  }
  if (key_flopped(&state.input.start)) {
    next_word();
  }

  /* end key input */

  /* rendering */

  int complete = hang_word_complete(state.word_ix, state.guessed);
  int dead = state.hang <= HANG_DEAD;
  hang_word_color_t word_color = complete ? HANG_P_COMPLETE
                               : dead ? HANG_P_DEAD
                               : HANG_P_NORMAL;

  keyboard_draw(state.keyboard.x, state.keyboard.y);
  hang_guessed_draw(state.guessed);
  hang_draw(state.hang);
  hang_word_draw(state.word_ix, state.guessed, word_color);

  /* end rendering */

  *(reg16 *)(IO_REG + IF) = ireq;

  *(reg16 *)(IO_REG + IME) = IME__INT_MASTER_ENABLE;
}

static const unsigned short palette_color[16] = {
  0, /* transparent */
  PRAM_RGB15(31, 31, 31), /* 1: white */
  PRAM_RGB15(31,  0,  0), /* 2: red */
  PRAM_RGB15(31, 31,  0), /* 3: yellow */
  PRAM_RGB15( 0, 31,  0), /* 4: green */
  PRAM_RGB15( 0, 31, 31), /* 5: cyan */
  PRAM_RGB15( 0,  0, 31), /* 6: blue */
  PRAM_RGB15(31,  0, 31), /* 7: magenta */

  PRAM_RGB15( 0,  0,  0), /* 8: black */
  PRAM_RGB15( 8,  8,  8), /* 9: grey */
  PRAM_RGB15( 8,  0,  0), /* 10: dark red */
  PRAM_RGB15( 8,  8,  0), /* 11: dark yellow */
  PRAM_RGB15( 0,  8,  0), /* 12: dark green */
  PRAM_RGB15( 0,  8,  8), /* 13: dark cyan */
  PRAM_RGB15( 0,  0,  8), /* 14: dark blue */
  PRAM_RGB15( 8,  0,  8), /* 15: dark magenta */
};

static const unsigned short palette_normal[16] = {
  0, /* transparent */
  PRAM_RGB15( 0,  0,  0), /* 1: black */
  PRAM_RGB15(31, 31, 31), /* 2: white */
};

static const unsigned short palette_inverse[16] = {
  0, /* transparent */
  PRAM_RGB15( 15, 31, 31), /* 1: white */
  PRAM_RGB15( 0,  0,  0), /* 2: black */
};

static const unsigned short palette_complete[16] = {
  0, /* transparent */
  PRAM_RGB15( 0,  0,  0), /* 1: black */
  PRAM_RGB15( 8, 31,  8), /* 2: green */
};

static const unsigned short palette_dead[16] = {
  0, /* transparent */
  PRAM_RGB15( 0,  0,  0), /* 1: black */
  PRAM_RGB15( 31, 8,  8), /* 2: red */
};

enum normal_color {
  NORMAL_BLACK = 1,
  NORMAL_WHITE = 2
};

enum inverse_color {
  INVERSE_WHITE = 1,
  INVERSE_BLACK = 2
};

void main(void)
{
  *(reg32 *)(IWRAM_USER_ISR) = (u32)(&_user_isr);

  *(reg16 *)(IO_REG + BG0CNT) =
    ( BG_CNT__COLOR_16_16
    | BG_CNT__SCREEN_SIZE(0) /* 256x256 */
    | BG_CNT__CHARACTER_BASE_BLOCK(0)
    | BG_CNT__SCREEN_BASE_BLOCK(31)
    | BG_CNT__PRIORITY(0)
    );

  *(reg16 *)(IO_REG + DISPCNT) =
    ( DISPCNT__BG0
    | DISPCNT__BG_MODE_0
    );

  copy_32((void *)(PRAM_BG + PRAM_PALETTE(0)),
          palette_normal,
          (sizeof (palette_normal)));

  copy_32((void *)(PRAM_BG + PRAM_PALETTE(1)),
          palette_inverse,
          (sizeof (palette_inverse)));

  copy_32((void *)(PRAM_BG + PRAM_PALETTE(2)),
          palette_color,
          (sizeof (palette_color)));

  copy_32((void *)(PRAM_BG + PRAM_PALETTE(3)),
          palette_complete,
          (sizeof (palette_complete)));

  copy_32((void *)(PRAM_BG + PRAM_PALETTE(4)),
          palette_dead,
          (sizeof (palette_dead)));

  for (int i = 0; i < 16; i++) {
    fill_32((void *)(VRAM + CHARACTER_BASE_BLOCK(0) + TILE_16(i)),
            nib_32(i),
            8 * 8 / 2);
  }

  glyph_init_8x8(NORMAL_WHITE, NORMAL_BLACK, TILE_16(16));
  glyph_init_8x16(NORMAL_WHITE, NORMAL_BLACK, TILE_16(48));

  *(reg16 *)(IO_REG + DISPSTAT) = DISPSTAT__V_BLANK_INT_ENABLE;

  *(reg16 *)(IO_REG + IE) =
    ( IE__V_BLANK
    );

  *(reg16 *)(IO_REG + IF) = (u16)-1;

  *(reg16 *)(IO_REG + IME) = IME__INT_MASTER_ENABLE;

  while (1) {
    *(reg8 *)(IO_REG + HALTCNT) = 0;
  }
}

void _start(void)
{
  while (1) main();
}
