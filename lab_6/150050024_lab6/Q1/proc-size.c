#include "types.h"
#include "stat.h"
#include "user.h"

int getpusz()
{
	uint curr = 0;

	uint pa = 0;

	int t = 0;
	for(uint i=0; i<0x80000000; i+=0x1000)
	{
		curr += get_va_to_pa(i, &pa, &t);
	}
	return curr<<12;
}
int getpksz()
{
	
	uint curr = 0;

	uint pa = 0;

	int t = 0;

	for(uint i=0x80000000; i>=0x80000000; i+=0x1000)
	{
		curr += get_va_to_pa(i, &pa, &t);
	}
	return curr<<12;
}

int getptsz()
{
	return getpusz() + getpksz();
}

int
main(int argc, char *argv[])
{
	char *buf;

	printf(1,"\ngetpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());
	printf(1,"getptsz: %d bytes\n",getptsz());


	buf=sbrk(4096);
	buf[0]='\0';
	printf(1,"\ngetpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());
	printf(1,"getptsz: %d bytes\n",getptsz());

	
	buf=sbrk(4096*7);
	printf(1,"\ngetpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());
	printf(1,"getptsz: %d bytes\n",getptsz());

	exit();
}