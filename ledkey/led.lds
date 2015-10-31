SECTIONS {
. = 0x02023400;
.text : { *(.text) }
.rodata ALIGN(4) : {*(.rodata*)}
.data ALIGN(4) : { *(.data*) }
.bss ALIGN(4) : { *(.bss) *(COMMON) }
}
