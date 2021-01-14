/*
		Author: Caraline Kneebone & Shane Combs
		Assignment Number: 2
		Date of Submission: 10/27/2020
		Name of this file: main.h
		Description of the program: This module contains file sharing struct information 
					for the Priority Scheduling program.
*/
#include <sys/types.h>

#define P_STARTED 1
#define P_STOPPED 0
#define PID_NOT_ASSIGNED -1 
#define HIGHER_FIRST 1
#define HIGHER_SECOND 0
#define ALL_P_TERMINATED 1
#define NOT_ALL_TERMINATED 0
#define YES 0
#define NO 1


struct process_information{
	int p_number;
	int at;
	int burst;
	int priority;
	long unsigned int starting_number;
	pid_t pid;
	int p_status_flag;
};

int proc_array_size();