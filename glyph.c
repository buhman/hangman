#include "base.h"
#include "register.h"
#include "type.h"

#include "res/font.glyph.h"

void glyph_init_8x8(u32 fg_color, u32 bg_color, u32 offset)
{
  u32 * vram = (u32 *)( VRAM
                      + CHARACTER_BASE_BLOCK(0)
                      + offset);
  u32 index = 0;
  for (u32 i = 0; i < (u32)(&_binary_res_font_8x8_glyph_size); i++) {
    u32 row_in = ((u8 *)&_binary_res_font_8x8_glyph_start)[i];
    u32 row_out = 0;
    for (u32 bit = 0; bit < 8; bit++)
      row_out |= (((row_in >> bit) & 1) ? fg_color : bg_color) << (bit * 4);

    vram[index++] = row_out;
  }
}

void glyph_init_8x16(u32 fg_color, u32 bg_color, u32 offset)
{
  u32 * vram = (u32 *)( VRAM
                      + CHARACTER_BASE_BLOCK(0)
                      + offset);
  u32 index = 0;
  for (u32 i = 0; i < (u32)(&_binary_res_font_8x16_glyph_size); i++) {
    u32 row_in = ((u8 *)&_binary_res_font_8x16_glyph_start)[i];
    u32 row_out = 0;
    for (u32 bit = 0; bit < 8; bit++)
      row_out |= (((row_in >> bit) & 1) ? fg_color : bg_color) << (bit * 4);

    vram[index++] = row_out;
  }
}
