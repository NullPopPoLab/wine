#include <stdio.h>
#include <stdlib.h>
#include "msdos.h"
#include "wine.h"

int do_int2f_16(struct sigcontext_struct *context);


int do_int2f(struct sigcontext_struct *context)
{
	switch((context->sc_eax >> 8) & 0xff)
	{
	case 0x10: /* share isn't installed */
	        EAX = (EAX & 0xffffff00) | 0x01;
		break;

	case 0x15: /* mscdex */
		/* ignore requests */
		return 1;

	case 0x16:
		return do_int2f_16(context);

	default:
		IntBarf(0x2f, context);
	};
	return 1;
}


int do_int2f_16(struct sigcontext_struct *context)
{
	switch(context->sc_eax & 0xff) {
		case 0x00: 
			/* return 'major/minor' for MSWin 3.1 */
			printf("do_int2f_16 // return 'major/minor' for MSWin 3.1 !\n");
			context->sc_eax = 0x0310;
			return 1;
		case 0x86: 
			/* operating in protected mode under DPMI */
			printf("do_int2f_16 // operating in protected mode under DPMI !\n");
			context->sc_eax = 0x0000;
			return 1;
		case 0x87: 
			printf("do_int2f_16 // return DPMI flags !\n");
			context->sc_eax = 0x0000;		/* DPMI Installed */
			context->sc_ebx = 0x0001;		/* 32bits available */
			context->sc_ecx = 0x04;			/* processor 486 */
			context->sc_edx = 0x0100;		/* DPMI major/minor */
			context->sc_esi = 0;			/* # of para. of DOS */
											/* extended private data */
			return 1;
		default:
			IntBarf(0x2f, context);
		}
	return 1;
}


