/* Linker script for ST STM32F103C8T6 */

MEMORY
{
	rom (rx) : ORIGIN = 0x0800 0000, LENGTH = 64K - 1K
	data (rwx) : ORIGIN = 0x0800FC00, LENGTH = 1K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

.user_data :
{
  . = ALIGN(4);
     *(.user_data)
  . = ALIGN(4);
} > data
