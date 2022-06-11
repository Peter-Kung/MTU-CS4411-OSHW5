# MTU-CS4411-OSHW5
## A Fake CPU Scheduler
In this assignment, you are to write a program, using signals (and "non-local" gotos if you like), to implement a fake scheduler. You do not and should not use ThreadMentor.
The major part of this programming assignment is to implement the following:

Periodically call one of the several given functions
Each function is assigned a time quantum. Once it is called, it can use the CPU for that amount of time (i.e., real time rather than CPU time). The call to these functions is in a round-robin order. Suppose the time quantum is set to 1 second and there are three functions, f1(), f2() and f3(). Then, f1() is called and runs for 1 second (i.e., real time); f2() is called and runs for 1 second; f3() is called and runs for 1 second; f1() is called and runs for 1 second; and so on. The default time quantum value is 1 second.
A Ctrl-C handler
This Ctrl-C handler should be activated when the system detects a Ctrl-C.
A Shell
The Ctrl-C handler should transfer the control to this shell for further processing. Once the shell is entered, it should display the following prompt:
Shell ->
This shell should start accepting commands until it encounters e, E, r or R. Each command starts with a single character and possibly followed by one or more integers.
e or E (exit): Exit the system. Thus, if a user enters e or E, your program should terminate immediately.
k or K (kill): Kill a function. This command requires a non-negative integer argument, giving the function ID to be killed. For example,
Shell -> k 2
Function 2 has been killed.
A killed function should not run again. If the integer argument indicates a function that does not exist (e.g., killed previously), you should display a message. For example, if function 4 was killed sometime ago, then
Shell -> k 4
Function 4 does not exist.
r or R (resume): Exit the shell and resume the function that was suspended when the Ctrl-C handler took over the control by calling it again. However, if this function was killed or suspended, the shell should call the next "runnable" function in the new order. This function should receive a full, new time quantum. If no function is runnable, the shell should print a message and wait for the next command from the user.
s or S (suspend): This command requires a non-negative integer, giving the function ID to be suspended. For example,
Shell -> s 2
Function 2 has been suspended.
After a function is suspended, it should not be run until it is activated again (by command a or A). If the ID gives a killed, a suspended, or even a non-exist function, you should display a message:
Shell -> s 2
Function 2 does not exist

Shell -> s 2
Function 2 was suspended
a or A (activate a suspended function): This command also requires a non-negative integer argument, indicating the function ID that should be activated. The function to be activated must be a suspended one; otherwise, you should display a message:
Shell -> a 2
Function 2 has been activated

Shell -> a 2
Function 2 is not a suspended one.
o or O (change execution order): This command changes the execution order of functions. It requires a permutation of integers 1, 2, 3, 4 and 5. For example,
Shell -> o 3 2 4 1 5
The execution order is now changed to 3 2 4 1 5
If all five functions are currently active, then the execution (or calling) order becomes f3(), f2(), f4(), f1() and f5(). However, if one or more of these functions were suspended or killed, the new order assigned to them is simply ignored. More precisely, if function f3() was suspended and f1() was killed, then the new execution order is f2(), f4() and f5(). In this case, your Shell should generate the following message to inform the user:
Shell -> o 3 2 4 1 5
Function 3 was suspended.  Assigned order ignored.
Function 1 was killed.  Assigned order ignored.
The execution order is changed to 2 4 5
However, after a suspended function is reactivated after this change, it should be executed in the given order. For example, if f3() is reactivated sometime later before another reordering, then the order is f3(), f2(), f4() and f5().
t or T (set time quantum): This command requires a positive integer argument, giving the new time quantum. For example,
Shell -> t 2
Time quantum has been set to 2 seconds
The above sets the time quantum to 2 seconds. Note that the shell should display a message about this change. This new time quantum also affects the function that is suspended due to a Ctrl-C key press.

## Input and Output
There is no input file. The output has already been defined in the funct5.c. There are five C functions, f1(), f2(), f3(), f4() and f5(), each of which produces its own output. The only output and possible input of your program are the commands to your Shell as shown in the previous section.
Click here to download a copy of funct5.c. Note that you should not change anything in this file, because the original version will be used for grading.

Program Specification
Please note the following specifications. Without observing these rules, you may risk lower grades.
You have to use functions in file funct5.c for scheduling purpose. You have to link these functions with your program files.
You have to implement all commands. While your shell is processing command input and output, all other events (e.g., Ctrl-C and alarm) must be masked off so that the shell will not be interfered. Since the system may not be able to keep up with your Ctrl-C key press, you might want to quickly hit Ctrl-C a few times.
Use signal.h and signal() to catch and handle signals. Other methods are simply unacceptable .
Feel free to use setjmp() and longjmp() to switch back and forth between user functions and your scheduler, although they really are not needed.
Use alarm() system call to simulate a time quantum.
