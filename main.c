#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include "./main.h"

int timeQuntum = 2;
jmp_buf JumpBuffer;
int main()
{
	signal(SIGINT, shell);
	int val = setjmp(JumpBuffer);
	switch(val) {
	case 0:
		f1();
	case 1:
		f2();
	case 2:
		f3();
	} 
}	


void shell(int argv) {
	if (argv == SIGINT) {	
		puts("");
		char a = 'n';
		char command[20] = {0};
		while(a != 'r') {
			printf("Shell -> ");
			fgets(command, 20, stdin);
			switch(command[0]) {
				case 'r':
				case 'R':
					a = 'r';
					break;
				case 'e':
				case 'E':
					exit(0);
				case 'k':
				case 'K':
					if(command[2] == '\0') {
						printf("Function does not exist\n");
						break;
					}
					printf("Function %c has been killed\n", command[2]);
					break;
				case 's':	
				case 'S':
					if(command[2] == '\0') {
						printf("Function does not exist\n");
						break;
					}
					printf("Function %c was suspended\n", command[2]);
					break;	
				case 'a':
				case 'A':
					if(command[2] == '\0') {
						printf("Function does not exist\n");
						break;
					}
					printf("Function %c has been activated\n", command[2]);
					break;
				case 'o':
				case 'O':
					if(command[2] == '\0') {
						printf("Function does not exist\n");
						break;
					}
					printf("The execution order is now changed to %s", command + 2);
					break;
				default:
					puts("unknown command");
					break;
			}
		}
	}
}
