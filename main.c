#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include "./main.h"

int timeQuntum = 2;
jmp_buf JumpBuffer;
extern void f1();
extern void f2();
extern void f3();
extern void f4();
extern void f5();


typedef struct pcb
{
	int processID;
	int status;
	void (*fn)(void);
	struct pcb *next;
} PCB;

static void init(PCB **, PCB **);

int main()
{
	PCB *cur = NULL;
	PCB *move = NULL;
	/* get ready queue */
	init(&cur, &move);
	signal(SIGINT, shell);
	int val = setjmp(JumpBuffer);
	if (val != 0)
		move = move->next;
	(move->fn)();
}	

static void init(PCB **cur, PCB **move)
{
	void (*fn[3])(void);
	fn[0] = f1;
	fn[1] = f2;
	fn[2] = f3;

	PCB **ptr = cur;
	for (int i = 1;i <= 3;++i) {
		*ptr = (PCB *)malloc(sizeof(PCB));
		(*ptr)->processID = i;
		(*ptr)->status   = RUNNING;
		(*ptr)->fn = fn[i - 1]; 
		ptr = &(*ptr)->next;
	}
	*ptr = *cur;
	*move = *cur;
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
