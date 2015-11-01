/*
 * Copyright (c) 2013 100ask
 *              http://www.100ask.net/
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
该工具的实际用法:
	mkbl2 u-boot.bin bl2.bin 14336
*/

int main (int argc, char *argv[])
{
	FILE		*fp;
	unsigned char	src;
	char		*Buf, *a;
	int		BufLen;
	int		nbytes, fileLen;
	int		count;
	unsigned int	checksum = 0;
	int		i;

	if (argc != 4)		// 如果参数个数不等于3，则打印使用帮助信息
	{
		printf("Usage: mkbl2 <source file> <destination file> <size> \n");
		return -1;
	}

	BufLen = atoi(argv[3]);				// 把字符串(14336)转换成整型数
	Buf = (char *)malloc(BufLen);		// 分配14K的缓存
	memset(Buf, 0x00, BufLen);			// 将该缓存清为0

	fp = fopen(argv[1], "rb");			// 以只读的方式打开原始bin文件(如u-boot.bin)
	if( fp == NULL)					// 如果为空，则表示打开失败
	{
		printf("source file open error\n");
		free(Buf);					// 释放刚刚分配的缓存
		return -1;
	}

	fseek(fp, 0L, SEEK_END);			// 让文件位置指针指向文件末尾，便于下行的统计大小的操作
	fileLen = ftell(fp);					// 用于得到文件位置指针当前位置相对于文件首的偏移字节数,即文件大小
	fseek(fp, 0L, SEEK_SET);				// 让文件位置指针指向文件开始

	/* 如果old.bin文件的大小小于规定的最大大小，则count等于该文件的大小，否则等于最大大小 */
	count = (fileLen < BufLen)? fileLen : BufLen;

	nbytes = fread(Buf, 1, count, fp);		// 从原始的bin文件(如u-boot.bin)中读取count大小的数据到Buf中

	if ( nbytes != count )				// 判断是否读取成功
	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	fclose(fp);							// 关闭刚刚打开的原始bin文件

	/* 得到BL2 + Signature */
	for(i = 0;i < (14 * 1024) - 4;i++)
	{
		checksum += (unsigned char)(Buf[i]);                //由此可知Signature就是一个unsigned int型的数
	}
	*(unsigned int*)(Buf+i) = checksum;

	fp = fopen(argv[2], "wb");
	if (fp == NULL)
	{
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}

	a	= Buf;						// 指向Buf的首地址
	nbytes	= fwrite( a, 1, BufLen, fp);	// 将得的到BL2 + Signature写入到目标文件中(bl2.bin)

	if ( nbytes != BufLen )				// 判断是否写入成功
	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	free(Buf);						// 做清理工作
	fclose(fp);

	return 0;
}

