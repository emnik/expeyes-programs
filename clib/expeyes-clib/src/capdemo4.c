/* 
Test program demonstrating Analog I/O functions.
Connect SINE to A1 before running the code. Compile & run using
$ gcc -Wall -o capdemo capdemo4.c -lm
$ ./capdemo4 > log.dat
$ xmgrace log.dat
*/

#include "ejlib.h" 
/* extern */ int fd;

void err(char* s)
{
fprintf(stderr,"Error: %s\n",s);
exit(0);
}

int main()
{
float fr, tvbuf[MAXBUF*2], *fp;		// Array to store Time & Voltage data from capture.
int	ch, ns, tg, k;

fd = open_eyesj();
if(fd < 0)
	{
	fprintf(stderr,"EYES Open Failed\n");
	exit(0);
	}

set_sqrs(100.0, 25, &fr);		// Sets 100Hz on SQR1 & SQR2 , with 50% phase difference

ns = 600;
tg = 100;

// Capture four channes, 8 bit resolution
ns = 450;
if(capture4(1, 6, 7, 1, ns, tg, tvbuf))err("capture4");
for(ch=0; ch < 4; ++ch)
	{
	fp = tvbuf + ch*2*ns;
	for(k=0; k < ns; ++k) printf("%f  %f\n", fp[k], fp[ns+k]);
	printf("\n");
	}

return 0;
}
