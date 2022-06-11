#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <ctype.h>
#include "./main.h"

int main()
{
	/* get ready queue */
	init(&readyQueue, &current, &head);
	signal(SIGINT, shell);
	int notFirstCall = setjmp(JumpBuffer);
	if (notFirstCall != 0)
		current = current->next;
	while (!current->fn || current->status == WAIT)
		current = current->next;
	(current->fn)();
}	

static void init(PCB **cur, PCB **move, PCB **head)
{
	fn[0] = f1;
	fn[1] = f2;
	fn[2] = f3;
	fn[3] = f4;
	fn[4] = f5;

	PCB **ptr = cur;
	for (int i = 1;i <= 3;++i) {
		*ptr = newProcess(i);
		ptr = &(*ptr)->next;
	}

	*head = (PCB*)malloc(sizeof(PCB));
	(*head)->processID = QUEUEHEAD;
	(*head)->fn = NULL;

	(*head)->next = *cur;
	*ptr = *head;
	*move = *cur;
}

PCB *newProcess(int i)
{
	PCB *ptr = (PCB *)malloc(sizeof(PCB));
	ptr->processID = i;
	ptr->status = RUNNING;
	ptr->fn = fn[i-1];
	return ptr;
}

void shell(int argv) {

	if (argv == SIGINT) {	
		puts("");
		char a = 'n';
		int val ;
		PCB *ptr = head->next;
		PCB *pre = head;
		PCB *processTable[PROCESSNUMBER] = {0};
		PCB *tempHead = NULL;
		PCB **newOrder = NULL;
		char command[30] = {0};
		char *strNum, *saveptr;
		int  *orderNum;

		while(a != 'r') {
input:
			for (int i = 0;i < PROCESSNUMBER;++i) {
				processTable[i] = 0;
			}

			
			ptr = head->next;
			pre = head;
			tempHead = NULL;
						
	
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
					val = atoi(command + 2);
					if(!head->next && (val == 0 || val >=  PROCESSNUMBER)) {
						printf("Function %s does not exist\n", command + 2);
						break;
					}

					/* Find target PCB */	
					while(ptr != head) {
						if (ptr->processID == val) {
							pre->next = ptr->next;
							free(ptr);
							printf("Function %c has been killed\n", command[2]);
							goto input;
						}
						/* continue check next PCB */
						pre = ptr;
						ptr = ptr->next;
					}	

					printf("Function %d does not exist\n", val);
					break;
				case 's':	
				case 'S':
					val = atoi(command + 2);
					if(!head->next && (val == 0 || val >=  PROCESSNUMBER)) {
						printf("Function %s does not exist\n", command + 2);
						break;
					}


					/* Find target PCB */	
					while(ptr != head) {
						if (ptr->processID == val) {
							ptr->status = WAIT;
							printf("Function %d was suspended\n", val);
							goto input;
						}
						/* continue check next PCB */
						pre = ptr;
						ptr = ptr->next;
					}	
						printf("Function %d does not exist\n", val);
					break;	
				case 'a':
				case 'A':
					val = atoi(command + 2);
					if(!head->next || (val == 0 || val >=  PROCESSNUMBER)) {
						printf("Function %s does not exist\n", command + 2);
						break;
					}

					/* Find target PCB */	
					while(ptr != head) {
						if (ptr->processID == val) {
							if (ptr->status == WAIT) {
								ptr->status = RUNNING;
								printf("Function %c has been activated\n", command[2]);		
							} else {
								printf("Function %c is not a suspended one.\n", command[2]);
							}
							goto input;
						}
						/* continue check next PCB */
						pre = ptr;
						ptr = ptr->next;
					}	
					/* not exist */
					if (val < PROCESSNUMBER) {
						pre->next = newProcess(val);
						pre->next->next = head;
						printf("Function %d has been activated\n", val);		
					} else {
						printf("%d out of range\n", val);
					}

					break;
				case 'o':
				case 'O':
					if(!head->next || command[2] == '\0') {
						printf("Function does not exist\n");
						break;
					}

					while (ptr != head) {
						processTable[ptr->processID] = ptr;
						ptr = ptr->next;
					}
					
					tempHead = (PCB *)malloc(sizeof(PCB));
					newOrder = &tempHead->next;

					strNum = strtok_r(command + 1, " ", &saveptr);
					while(strNum) {
						val = atoi(strNum);
						if (val == 0 || val >= PROCESSNUMBER) {
							printf("Function %s does not exist\n", strNum);
							goto input;
						}		
						
						/* if process not exist */						
						if (processTable[val] == NULL) {
							printf("Function %d was killed. Assigned order ignored.\n", val);
						} else {
							*newOrder = processTable[val];
							newOrder = &(*newOrder)->next;					
						if (processTable[val]->status == WAIT)
							printf("Function %d was suspended. Assigned order ignored.\n", val);
						}
						/* if process wait status */
						strNum = strtok_r(NULL, " ", &saveptr);
					}	
					head->next = tempHead->next;
					*newOrder = head;
					free(tempHead);

					printf("The execution order is now changed to ");
					ptr = head->next;
					while (ptr != head) {
						if (ptr->status == RUNNING)
							printf("%d ", ptr->processID);
						ptr = ptr->next;
					}	
					puts("");
					break;
				case 't':
				case 'T':
					val = atoi(command + 2);
					if (val == 0) {
						printf("Invalid second: %s\n", command + 2);
						break;
					}
					timeQuntum = val;
					printf("Time Quantum has been set to %d srconds\n", timeQuntum);
					break;
				default:
					puts("unknown command");
					break;
			}
		}
	}
}
