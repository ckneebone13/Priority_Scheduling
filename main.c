/*
		Author: Caraline Kneebone & Shane Combs
		Assignment Number: 2
		Date of Submission: 10/27/2020
		Name of this file: main.c
		Description of the program: main entry point, handles process creation and timer functions
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include "main.h"

int sec;
struct process_information* temp;
struct process_information* running_process;
struct process_information* next_process;

void increment_sec(void);
void interval_timer();
void run_proc(struct process_information* running_proc);
int check_priority(struct process_information* p1, struct process_information* p2);
void set_next();
int finished();

/*
Function Name: main
Input to the method: argc and argv
Output(Return value): void
Brief description of the task: start timer and alarm, set struct varibles, 
*/
void main(int argc, char *argv[]){
	//set both processes that will execute with prime
	running_process = NULL;
	next_process = NULL;
	// make the buffer and fill it
	temp = malloc(sizeof(struct process_information)*1);
	parse_process_info(temp);//pass stdin file to be parsed
	// Set the first process to be run the first process in the file
	running_process = &temp[0];
	interval_timer();//initiate timer
	//install timer
	while(1){
		signal(SIGALRM, (void (*)(int)) increment_sec);//kernal timer continue forever
	}
}

/*
Function Name: interval_timer
Input to the method: void
Output(Return value): void
Brief description of the task: keeps time for the program
*/
void interval_timer(){
	sec = 0;
	struct itimerval it_val;

	// Install timer_handler as the signal handler for SIGALRM. 
	if (signal(SIGALRM, (void (*)(int)) increment_sec) == SIG_ERR) {//check if call fails
		perror("Unable to catch SIGALRM");
		exit(1);
	}
	// The timer goes off 1 second after installation of the timer.
	it_val.it_value.tv_sec = 1;
	it_val.it_value.tv_usec = 0;
	// ... and every 1 second after that.
	it_val.it_interval = it_val.it_value;

	//Start a real timer. It counts down whenever this process is executing.
	setitimer(ITIMER_REAL, &it_val, NULL);
}

/*
Function Name: increment_sec
Input to the method: void
Output(Return value): void
Brief description of the task:checks for which process to run, 
	checks if proces is finished, checks if correct process is running
*/
void increment_sec(void) {
	if(running_process->at <= sec && //process not yet running
		running_process->pid == PID_NOT_ASSIGNED && //no assigned pid
		running_process->p_status_flag == P_STOPPED){//process not running
		run_proc(running_process);// send it to run
	}

	if(running_process->burst == 0){//if burst is over
		running_process->p_status_flag = P_STARTED;
		kill(running_process->pid,SIGTERM);//process terminated
		running_process = next_process;//start next process
		next_process = NULL;//unassign next process memory
		if(finished()){//if process is complete, quit
			exit(1);
		}
	}
	
	if(check_priority(next_process, running_process)){//if other process has higher priority
		kill(running_process->pid, SIGTSTP);//pause running process
		running_process = next_process;//assign next process to run
		next_process = NULL;
		if(running_process->pid == PID_NOT_ASSIGNED){//send to run if hasn't already
			run_proc(running_process);
		} 
		else{
			kill(running_process->pid, SIGCONT);//resume process
		}
	}
	
	set_next();//figure out next process to run based on priority
	running_process->burst--;//update running process burst
	sec++;//update seconds
}



/*
Function Name: check_priority
Input to the method: two processes to check
Output(Return value): process 1 or process 2
Brief description of the task: Handles Ties by checking priority and arrival time 
								to see which process is up next
*/
int check_priority(struct process_information* p1, struct process_information* p2){
	if(p1->priority < p2->priority){//process 2 has greater priority
		return HIGHER_FIRST;
	} 
	else if(p1->priority > p2->priority){//process 1 has greater priority
		return HIGHER_SECOND;
	} 
	else if(p1->priority == p2->priority){//process 1&2 have same priority
		if(p1->at < p2->at){//process 1 has earlier arrival time
			return HIGHER_FIRST;
		} 
		else if(p1->at > p2->at){//process 2 has earlier arrival time
			return HIGHER_SECOND;
		} 
		else{//if same, continue with process 1
			return HIGHER_FIRST;
		}
	}
}

/*
Function Name: set_next
Input to the method: void
Output(Return value): void
Brief description of the task: sets up the next process based on priority
*/
void set_next(){
	int i;
	struct process_information* up_next_p = NULL;
	for(i = 0; i < proc_array_size(); i++){
		if(&temp[i] != running_process){//not currently running proc
			if(&temp[i].p_status_flag == P_STOPPED &&// not running
				check_priority(&temp[i], up_next_p) && //higher priority than running
				temp[i].at <= sec){//arrival time tie breaker
				up_next_p = &temp[i];//set as next
			}
		}
	}
	next_process = up_next_p;
}

/*
Function Name: run_proc
Input to the method: 1 processes
Output(Return value): void
Brief description of the task: forks process to execute prime.o
*/
void run_proc(struct process_information* running_proc){
	pid_t pid = fork();//fork 
	
	if(pid == 0){//set variables to pass on as strings to read from argv
		char p_num[15];
		char priority[15];
		char starting_number[15];
		//start execution of process with necessary args
		sprintf(p_num, "%i", running_proc->p_number);//send p number
		sprintf(priority, "%i", running_proc->priority);//send priority
		sprintf(starting_number, "%lu", running_proc->starting_number);//send number to start prime program with
		
		execlp("./prime.o", "./prime.o",
			(char*)p_num, (char*)priority,
			(char*)starting_number, (char*)NULL);//send args and execute prime.o
	} 
	else{
		running_proc->pid = pid;//save child's id
	}
}

/*
Function Name: finished
Input to the method: void
Output(Return value): status of terminated processes
Brief description of the task: checks process array to find running processes
*/
int finished(){
	int i;
	for(i = 0; i < proc_array_size(); i++){//loop through process array
		if(temp[i].p_status_flag == P_STARTED)//if a process is found that is still running
			return NOT_ALL_TERMINATED;
	}
	return ALL_P_TERMINATED;
}
