/* Script for -z combreloc: combine and sort reloc sections */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",
	      "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
/* SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib"); */
/* Do we need any of these for elf?
   __DYNAMIC = 0;    */
SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__executable_start = 0x00000000); . = 0x00000000;
  /* + SIZEOF_HEADERS; */
  .text           :
  {
    *(.text .stub .text.* .gnu.linkonce.t.*)
    KEEP (*(.text.*personality*))
    /* .gnu.warning sections are handled specially by elf32.em.  */
  } =0
  .fini :
  {
    KEEP (*(.fini))
  } =0
  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);
  .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) }
  .rodata1        : { *(.rodata1) }
  .eh_frame_hdr : { *(.eh_frame_hdr) }
  .eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) }
  . = ALIGN (0x8000) - ((0x8000 - .) & (0x8000 - 1));
  . = DATA_SEGMENT_ALIGN (0x8000, 0x1000);
  .eh_frame : ONLY_IF_RW { KEEP (*(.eh_frame)) }
  .data           :
  {
    __data_start = . ;
    *(.data .data.* .gnu.linkonce.d.*)
    KEEP (*(.gnu.linkonce.d.*personality*))
    SORT(CONSTRUCTORS)
  }
  .data1          : { *(.data1) }
  _edata = .;
  PROVIDE (edata = .);
  __bss_start = .;
  __bss_start__ = .;
  .bss            :
  {
   *(.dynbss)
   *(.bss .bss.* .gnu.linkonce.b.*)
   *(COMMON)
   /* Align here to ensure that the .bss section occupies space up to
      _end.  Align after .bss to ensure correct alignment even if the
      .bss section disappears because there are no input sections.  */
   . = ALIGN(32 / 8);
  }
  . = ALIGN(32 / 8);
  _end = .;
  _bss_end__ = . ; __bss_end__ = . ; __end__ = . ;
  PROVIDE (end = .);
  . = DATA_SEGMENT_END (.);
  /DISCARD/ : { *(.note.GNU-stack) }
}

