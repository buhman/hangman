#include <stdio.h>
#include <ctype.h>

size_t transform_buf(unsigned char * dst, const unsigned char * src, size_t rlen)
{
  size_t wlen = 0;

  for (size_t ix = 0; ix < rlen; ix++) {
    unsigned char c = src[ix];
    switch (c) {
    case 'a' ... 'z':
      dst[wlen++] = c - 'a';
      break;
    case 'A' ... 'Z':
      dst[wlen++] = c - 'A';
      break;
    case '\n':
      while (wlen % 16 != 0) {
        dst[wlen++] = (unsigned char)-1;
      }
      continue;
    default:
      fprintf(stderr, "invalid char %d %c at ix %ld\n", c, c, ix);
      break;
    }
  }

  return wlen;
}

int main(void)
{
  unsigned char rbuf[4096];
  unsigned char wbuf[4096 * 14];
  size_t rlen;
  size_t wlen;

  while ((rlen = fread(rbuf, (sizeof (rbuf[0])), (sizeof (rbuf)), stdin)) > 0) {
    wlen = transform_buf(wbuf, rbuf, rlen);
    fwrite(wbuf, (sizeof (wbuf[0])), wlen, stdout);
  }

  return 0;
}
