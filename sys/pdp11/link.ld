ENTRY(_pdp11_entry)

SECTIONS {
    .text 0x0000 :
    {
        *(.text .text.*)
    }

    .data 0x0000 :
    {
        *(.data .data.*)
        *(.rodata .rodata.*)
    }

    .bss (NOLOAD) :
    {
        *(.bss .bss.*)
        *(COMMON)
    }
}