#include "base.h"
#include "register.h"
#include "type.h"
#include "hang.h"
#include "keyboard.h"
#include "res/words.binlst.h"

static inline void set_tile(int x, int y, int n)
{
  *(reg16 *)( VRAM
            + SCREEN_BASE_BLOCK(31)
            + (((y * 32) + x) * 2)
            ) = SCREEN_TEXT__PALETTE(2) | n;
}

static u8 hang_colors[HANG__LAST] = {
  [HANG_DEAD] = 0,
  [HANG_BASE] = 11,
  [HANG_MAST] = 13,
  [HANG_CRANE] = 9,
  [HANG_ROPE] = 15,
  [HANG_NOOSE] = 12,
  [HANG_HEAD] = 2,
  [HANG_BODY] = 3,
  [HANG_LEFT_ARM] = 7,
  [HANG_RIGHT_ARM] = 5,
  [HANG_LEFT_FOOT] = 4,
  [HANG_RIGHT_FOOT] = 6,
};

static inline void part_draw(int part, int color)
{
  switch (part) {
  case HANG_RIGHT_FOOT:
  // right foot
  set_tile(20, 13, color);
  set_tile(21, 13, color);
  break;

  case HANG_LEFT_FOOT:
  // left foot
  set_tile(17, 13, color);
  set_tile(18, 13, color);
  break;

  case HANG_RIGHT_ARM:
  // right arm
  set_tile(20, 10, color);
  set_tile(21, 10, color);
  break;

  case HANG_LEFT_ARM:
  // left arm
  set_tile(17, 10, color);
  set_tile(18, 10, color);
  break;

  case HANG_BODY:
  // body
  set_tile(19, 12, color);
  set_tile(19, 11, color);
  set_tile(19, 10, color);
  set_tile(19, 9, color);
  break;

  case HANG_HEAD:
  // head
  set_tile(18, 6, color);
  set_tile(19, 6, color);
  set_tile(20, 6, color);
  set_tile(18, 7, color);
  set_tile(19, 7, color);
  set_tile(20, 7, color);
  set_tile(18, 8, color);
  set_tile(19, 8, color);
  set_tile(20, 8, color);
  break;

  case HANG_NOOSE:
  // noose
  set_tile(17, 5, color);
  set_tile(18, 5, color);
  set_tile(19, 5, color);
  set_tile(20, 5, color);
  set_tile(21, 5, color);
  break;

  case HANG_ROPE:
  // rope
  set_tile(19, 4, color);
  break;

  case HANG_CRANE:
  // crane
  set_tile(19, 3, color);
  set_tile(20, 3, color);
  set_tile(21, 3, color);
  set_tile(22, 3, color);
  set_tile(23, 3, color);
  set_tile(24, 3, color);
  break;

  case HANG_MAST:
  // mast
  set_tile(24, 4, color);
  set_tile(24, 5, color);
  set_tile(24, 6, color);
  set_tile(24, 7, color);
  set_tile(24, 8, color);
  set_tile(24, 9, color);
  set_tile(24, 10, color);
  set_tile(24, 11, color);
  set_tile(24, 12, color);
  set_tile(24, 13, color);
  break;

  case HANG_BASE:
  // base
  set_tile(23, 14, color);
  set_tile(24, 14, color);
  set_tile(25, 14, color);
  set_tile(26, 14, color);
  break;
  }
}

void hang_draw(u8 hang)
{
  for (int part = HANG_DEAD; part < HANG__LAST; part++) {
    int color = hang >= part ? hang_colors[part] : 0;
    part_draw(part, color);
  }
}

void hang_guessed_draw(u32 guessed)
{
  for (int i = 0; i < 26; i++) {
    int tile;
    if (guessed & (1 << i)) {
      tile = (16 + i);
    } else {
      tile = 0;
    }
    *(reg16 *)( VRAM
              + SCREEN_BASE_BLOCK(31)
              + ((32 + 2 + i) * 2)) = tile;
  }
}

static const u8 * words = (const u8 *)(&_binary_res_words_binlst_start);
//static const u32 words_size = (const u32)(&_binary_res_words_bin_size);

void hang_word_draw(u32 word_ix, u32 guessed, hang_word_color_t color)
{
  int ix = 0;
  u8 c;
  int tile = 0;
  while (ix < 15) {
    c = words[word_ix * 16 + ix++];
    if (c == (u8)-1)
      tile = 0;
    else if (color != HANG_P_NORMAL || guessed & (1 << c))
      tile = 48 + (c * 2);
    else
      tile = 48 + (_UNDERSCORE * 2);

    *(reg16 *)( VRAM
              + SCREEN_BASE_BLOCK(31)
              + ((32 * 9 + 1 + ix) * 2)
              ) = SCREEN_TEXT__PALETTE(color) | (tile);

    *(reg16 *)( VRAM
              + SCREEN_BASE_BLOCK(31)
              + ((32 * 10 + 1 + ix) * 2)
              ) = SCREEN_TEXT__PALETTE(color) | (tile + 1);
  }
}

int hang_letter_in_word(u32 word_ix, u8 needle)
{
  int ix = 0;
  u8 c;
  while ((c = words[word_ix * 16 + ix++]) != (u8)-1) {
    if (c == needle)
      return 1;
  }
  return 0;
}

int hang_word_complete(u32 word_ix, u32 guessed)
{
  int ix = 0;
  u8 c;
  while ((c = words[word_ix * 16 + ix++]) != (u8)-1) {
    if (!(guessed & (1 << c)))
      return 0;
  }
  return 1;
}
