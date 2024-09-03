#include <pico/bootrom.h>

#include "pico-tiny.h"

void
__attribute__((noreturn))
__printflike(1, 0)
tiny_panic(__unused const char *fmt, ...)
{
	(void) fmt;
	reset_usb_boot(0, 0);
}

int main(void)
{
	return 0;
}
