SECTIONS
{
	. = 0x02023400;
	.text : {
		start.o
		* (.text)
	}
    		
	.data : {
		* (.data)
	}
	
	bss_start = .; 
	.bss : {
		* (.bss)
	}
	bss_end  = .;	
}
