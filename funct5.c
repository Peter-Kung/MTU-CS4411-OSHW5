#include  <stdio.h>
#include  <stdlib.h>
#include <setjmp.h>
#define   MAX_RANDOM   100000L

extern int timeQuntum;
extern jmp_bug JumpBuffer;
void  Delay(void)
{
     long  i;
     int   x;
     
     for (i = 0; i < MAX_RANDOM; i++)
          x = rand();
}

void  f1(void)
{
     int val = 0;
     while (val <= timeQuntum) {
          printf("This is from thread 1\n");
          Delay();
	  val++;
     }
     longjmp(JumpBuffer, 1);
}

void  f2(void)
{
     int val = 0;
     while (val <= 2) {
          printf("   This is from thread 2\n");
          Delay();
	 val++;
     }
     longjmp(JumpBuffer, 2);
}


void  f3(void)
{
     int val = 0;
     while (val <= 2) {
          printf("      This is from thread 3\n");
          Delay();
	val++;
     }
	longjmp(JumpBuffer, 0);
}

void  f4(void)
{
     while (1) {
          printf("         This is from thread 4\n");
          Delay();
     }
}

void  f5(void)
{
     while (1) {
          printf("            This is from thread 5\n");
          Delay();
     }
}


