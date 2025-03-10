OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
 . = 0x20480;
 . = ALIGN(4);
 .head :
 {
  main/sboot_head.o (.rodata)
 }
 .text :
 {
  /home/ubuntu/tina-d1-h/lichee/brandy-2.0/spl/arch/arm/cpu/armv7/sboot_entry.o (.text)
  *(.text)
 }
 . = ALIGN(16);
   .rodata : { *(.rodata) }
 . = ALIGN(16);
   .data : { *(.data) }
 . = ALIGN(4);
 .bss :
 {
 __bss_start = .;
  *(.bss)
 }
 . = ALIGN(4);
 __bss_end = .;
 _end = .;
}
