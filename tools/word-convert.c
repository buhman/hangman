#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

#include <utf8proc.h>

ssize_t transform_buf(unsigned char * dst, size_t * wlen, const unsigned char * src, const size_t rlen)
{
  fprintf(stderr, "trs\n");

  ssize_t ret;
  int32_t codepoint;
  const unsigned char * bufi = src;
  size_t leni = rlen;

  while (leni > 0) {
    ret = utf8proc_iterate(bufi, leni, &codepoint);
    if (ret == -1)
      break;
    codepoint = utf8proc_toupper(codepoint);

#define A_CIRCUMFLEX (194) // 26
#define I_CIRCUMFLEX (206) // 27
#define A_BREVE (258)      // 28
#define S_COMMA (536)      // 29
#define T_COMMA (538)      // 30

    switch (codepoint) {
    case 'A' ... 'Z':
      dst[(*wlen)++] = codepoint - 'A';
      break;
    case A_CIRCUMFLEX:
      dst[(*wlen)++] = 26;
      break;
    case I_CIRCUMFLEX:
      dst[(*wlen)++] = 27;
      break;
    case A_BREVE:
      dst[(*wlen)++] = 28;
      break;
    case S_COMMA:
      dst[(*wlen)++] = 29;
      break;
    case T_COMMA:
      dst[(*wlen)++] = 30;
      break;
    case '\n':
      while (*wlen % 16 != 0) {
        dst[(*wlen)++] = (unsigned char)-1;
      }
      break;
    default:
      fprintf(stderr, "invalid char %d at ix %ld\n", codepoint, bufi - src);
      return -1;
      break;
    }

    bufi += ret;
    leni -= ret;
  }

  return rlen - leni;
}

int main(void)
{
  unsigned char rbuf[4096];
  unsigned char wbuf[4096 * 14];
  size_t rlen;
  size_t wlen = 0;
  size_t wlen_p;
  int ret;
  int roffset = 0;

  while ((rlen = fread(rbuf + roffset, (sizeof (rbuf[0])), (sizeof (rbuf)) - roffset, stdin)) > 0) {
    ret = transform_buf(wbuf, &wlen, rbuf, rlen + roffset);
    if (ret < 0)
      return -1;
    memmove(rbuf, rbuf + ret, rlen - ret);
    roffset = rlen - ret;

    fwrite(wbuf, (sizeof (wbuf[0])), wlen - wlen_p, stdout);

    wlen_p = wlen;
  }

  return 0;
}
