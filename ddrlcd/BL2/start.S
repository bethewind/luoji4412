.text
.globl _start
_start:

      // 关闭看门狗
      ldr	r0, =0x10060000
      mov	r1, #0
      str	r1, [r0]
      
      // 打开icache可提高运行速度
      mrc	p15, 0, r0, c1, c0, 0
      //orr	r0, r0, #0x00001000      //打开ICache
      //bic	r0, r0, #0x00001000      //关闭ICache
      mcr	p15, 0, r0, c1, c0, 0
       
      ldr sp, =0x02027800 // 调用C函数之前必须设置栈,栈用于保存运行环境,给局部变量分配空间
                        // 参考ROM手册P14, 我们把栈指向BL2上方1K处(1K已经够用),
                        // 即:0x02020000 (iRAM基地址) + 5K(iROM代码用) + 8K(BL1用) + 16K(BL2用) + 1K(用作栈))
      bl system_clock_init // 调用时钟初始化函数
      
      //bl uart_asm_init  /* init uart for debug */
      
      bl mem_init     //初始化DDR SDRAM
      
      bl copy_code_to_dram     //重定位，并跳到DRAM中运行
	

halt:
	b halt
