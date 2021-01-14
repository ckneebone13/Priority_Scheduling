# Priority_Scheduling
Input Example: ./a.out input.txt


Assume input.txt contains the following lines.
(Note that number below contain Process number, Arrival Time, Burst and Priorities)
0 1 6 3
1 2 4 2
2 2 2 1
3 4 6 2
4 6 4 3
5 7 2 4
Scheduler: Time Now: 1 second
Scheduling to Process 0 (Pid 1234)


Output Example:
(When a process scheduled for the first time, it prints the following)
Process 0: My priority is 2, my PID is 1314: I just got started.
I am starting with the number 233343434 to find the next prime number.

Scheduler: Time Now: 4 seconds
Suspending Process 2 (Pid 1235)and Resuming Process 0 (Pid 1234)

(When a process is suspended… it prints the following)
Process 0: My priority is 2, my PID is 1314: I am about to be suspended... Highest prime number I found is 5754853343.

(When a process is resumed… it prints the following)
Process 0: My priority is 2, my PID is 1314: I just got resumed.
Highest prime number I found is 57548533422.

Scheduler: Time Now: 8 seconds
Terminating Process 2 (Pid 1235)

(When a process ends... it prints the following)
Process 0: My priority is 2, my PID is 1314: I completed my task and I am exiting. Highest prime number I found is 1000000000063.


To Run: Download to a linux system: file_parser.c, main.h, main.c, prime.c, and compile files

Run the following command ONLY once to turn our compile script into and executable.: chmod +x compile

To complile the program run the following command: ./a.out < input.txt

This programs runs with some exceptions to the instructions:
The run command is different from the one specified in the instructions due to reading from stdin.
Our program's command: ./a.out < input.txt
Specified command: ./a.out input.txt

This program has issues with the following:
Unable to properly print prime numbers.
Unable to loop through processes in order to fork and run them.

This program is successful with the following:
Handling fork and timer operations.
Demo will show details.
