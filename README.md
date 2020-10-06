# stdio

sprintf, printf for FreeRTOS

sprintf: re-create this function
printf: re-create and re-target this function

Test for FreeRTOS on SiFive HiFive Rev B 01

## Usage:
	putchar is the only external dependency for this file,
	if you have a working putchar, leave it commented out.
	If not, uncomment the define below and
	replace outbyte(c) by your own function call.

## Other codes here:
- A tiny printf for embedded applications (http://www.sparetimelabs.com/tinyprintf/tinyprintf.php)