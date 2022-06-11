#define RUNNING 1
#define WAIT 2
#define PROCESSNUMBER 6
#define QUEUEHEAD -1
void shell(int );
int timeQuntum = 2;
jmp_buf JumpBuffer;

typedef struct pcb
{
	int processID;
	int status;
	void (*fn)(void);
	struct pcb *next;
} PCB;


void (*fn[5])(void);
PCB *head = NULL;
PCB *readyQueue = NULL;
PCB *current = NULL;
PCB *waitQueue = NULL;

static void init(PCB **, PCB **, PCB **);
PCB *newProcess(int);
extern void f1();
extern void f2();
extern void f3();
extern void f4();
extern void f5();


