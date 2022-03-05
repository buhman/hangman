#include "type.h"

typedef enum hang {
  HANG_DEAD = 0,
  HANG_BASE,
  HANG_MAST,
  HANG_CRANE,
  HANG_ROPE,
  HANG_NOOSE,
  HANG_HEAD,
  HANG_BODY,
  HANG_LEFT_ARM,
  HANG_RIGHT_ARM,
  HANG_LEFT_FOOT,
  HANG_RIGHT_FOOT,
  HANG__LAST
} hang_t;

typedef enum hang_word_color {
  HANG_P_NORMAL = 0,
  HANG_P_COMPLETE = 3,
  HANG_P_DEAD = 4,
} hang_word_color_t;

void hang_word_length_init(void);
void hang_entropy(u32 e);
u32 hang_next_word_index(void);
void hang_draw(u8 hang);
void hang_guessed_draw(u32 guessed);
void hang_word_draw(u32 word_ix, u32 guessed, hang_word_color_t color);
int hang_letter_in_word(u32 word_ix, u8 needle);
int hang_word_complete(u32 word_ix, u32 guessed);
