#include <stdio.h>
#include <assert.h>

#include <ft2build.h>
#include FT_FREETYPE_H

int load_char(FT_Face face, FT_ULong char_code, unsigned char * buf)
{
  FT_Error error;
  FT_UInt glyph_index = FT_Get_Char_Index(face, char_code);

  error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
  if (error) {
    printf("FT_Load_Glyph %s\n", FT_Error_String(error));
    return 0;
  }

  assert(face->glyph->format == FT_GLYPH_FORMAT_BITMAP);
  assert(face->glyph->bitmap.num_grays == 2);
  assert(face->glyph->bitmap.pitch == 1);
  assert(face->glyph->bitmap.width <= 8);
  assert(face->glyph->bitmap.rows == 8 || face->glyph->bitmap.rows == 16);

  for (int y = 0; y < (int)face->glyph->bitmap.rows; y++) {
    char row = face->glyph->bitmap.buffer[y];
    unsigned char row_out = 0;
    for (int x = 0; x < 8; x++) {
      int bit;
      if (x < (int)face->glyph->bitmap.width) {
        bit = (row >> (7 - x)) & 1;
      } else {
        bit = 0;
      }
      //fprintf(stderr, bit ? "█" : " ");
      row_out |= (bit << x);
    }
    //fprintf(stderr, "\n");
    buf[y] = row_out;
  }

  return face->glyph->bitmap.rows;
}

int main(int argc, char *argv[])
{
  FT_Library library;
  FT_Face face;
  FT_Error error;

  if (argc < 2) {
    fprintf(stderr, "argc");
    return -1;
  }

  error = FT_Init_FreeType(&library);
  if (error) {
    fprintf(stderr, "FT_Init_FreeType\n");
    return -1;
  }

  error = FT_New_Face(library, argv[1], 0, &face);
  if (error) {
    fprintf(stderr, "FT_New_Face\n");
    return -1;
  }

  error = FT_Select_Size(face, 0);
  if (error) {
    fprintf(stderr, "FT_Select_Size: %s %d\n", FT_Error_String(error), error);
    return -1;
  }

  unsigned char buf[(('_' - 'A') + 1) * face->available_sizes[0].height];
  int ret;
  unsigned char * bufi = buf;
  for (int c = 'A'; c <= '_'; c++) {
    ret = load_char(face, c, bufi);
    if (ret == 0)
      return -1;
    bufi += ret;
  }

  fwrite(buf, (sizeof (buf[0])), (sizeof (buf)) / (sizeof (buf[0])), stdout);
}
