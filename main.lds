OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
  gprom : ORIGIN = 0x8000000, LENGTH = 32M
  iwram : ORIGIN = 0x3000000, LENGTH = 32K
  ewram : ORIGIN = 0x2000000, LENGTH = 256K
}
SECTIONS
{
  . = 0x8000000;

  .text ALIGN(4) : SUBALIGN(1)
  {
    KEEP(*(.rom.start_addr))
    KEEP(*(.rom.nintendo_logo))
    KEEP(*(.rom.header))
    *(.text.load)
  } >gprom AT> gprom

  /* text */

  . = 0x3000000;

  rom.text ALIGN(32) : SUBALIGN(4)
  {
    *(.text*)
    . = (. + 0x1f) & ~0x1f;
  } >iwram AT> gprom

  __text_link_start = ADDR(rom.text);
  __text_link_end = ADDR(rom.text) + SIZEOF(rom.text);
  __text_load_start = LOADADDR(rom.text);

  /* data */

  rom.data ALIGN(32) : SUBALIGN(4)
  {
    *(.data)
    . = (. + 0x1f) & ~0x1f;
  } >iwram AT> gprom

  __data_link_start = ADDR(rom.data);
  __data_link_end = ADDR(rom.data) + SIZEOF(rom.data);
  __data_load_start = LOADADDR(rom.data);

  /* bss */

  rom.bss ALIGN(32) : SUBALIGN(4)
  {
    *(.bss)
    . = (. + 0x1f) & ~0x1f;
  } >iwram AT> gprom

  __bss_link_start = ADDR(rom.bss);
  __bss_link_end = ADDR(rom.bss) + SIZEOF(rom.bss);

  /* rodata */

  rom.rodata ALIGN(32) : SUBALIGN(4)
  {
    *(.rodata)
    . = (. + 0x1f) & ~0x1f;
  } >iwram AT> gprom

  __rodata_link_start = ADDR(rom.rodata);
  __rodata_link_end = ADDR(rom.rodata) + SIZEOF(rom.rodata);
  __rodata_load_start = LOADADDR(rom.rodata);
}
