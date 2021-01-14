/*
		Author: Caraline Kneebone & Shane Combs
		Assignment Number: 2
		Date of Submission: 10/27/2020
		Name of this file: file_parser.c
		Description of the program: Parses input file...
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

void parse_process_info(struct process_information* process_info_array);
long unsigned int ten_dig_num_generator();
int array_size;

/*
Function Name: parse_process_info
Input to the method: empty process arry
Output(Return value): void
Brief description of the task: parse input file, create process array to hold all processes
*/
void parse_process_info(struct process_information* process_info_array){
	array_size = 0;
	//temp variables to be added to process info array
	int p_number_t = 0;
	int at_t = 0;
	int burst_t = 0;
	int priority_t = 0;
	//use scanf to read directly from stndin - must use ./a.out < input.txt
	while(scanf("%i %i %i %i", &p_number_t, &at_t, 
				&burst_t, &priority_t) != EOF){
		//must create new process for every line of input file
		struct process_information new_line;
		new_line.p_number = p_number_t;
		new_line.at = at_t;
		new_line.burst = burst_t;
		new_line.priority = priority_t;
		new_line.starting_number = ten_dig_num_generator();
		new_line.pid = PID_NOT_ASSIGNED;
		new_line.p_status_flag = P_STOPPED;
		array_size++;//resize array
		//resize memory block to allocate process information array length size to hold new attributes
		process_info_array = realloc(process_info_array, sizeof(struct process_information) * array_size);
		process_info_array[array_size - 1] = new_line;
		/*printf("starting number: %lu pid: %d p_number: %d AT: %d burst: %d priority: %d status flag: %d\n", 
            new_line.starting_number, new_line.pid, new_line.p_number, new_line.at, burst_t, 
            new_line.priority, new_line.p_status_flag);*/
	}
}

/*
Function Name: ten_dig_num_generator
Input to the method:  void
Output(Return value): random number - 10 digits in length
Brief description of the task: uses rand to generate a random number of desired length
*/
long unsigned int ten_dig_num_generator(){
    long unsigned int rand_num = 0;
    long unsigned int max_size = 10000000000;
    long unsigned int min_size = 1000000000;
    
    //srand(time(0));//caused number generator
    //while (rand_num <= 10000000000 && rand_num > 1000000000){
    //    rand_num = (rand());
    //}
    rand_num = (rand() % (max_size + 1 - min_size) + min_size);

    //printf("Random value on [0,%d]: %lu\n", RAND_MAX, rand_num);
    return(rand_num);
}

/*
Function Name: proc_array_size
Input to the method:  void
Output(Return value): int
Brief description of the task: returns size of process array to main.c
*/
int proc_array_size(){
	return array_size;
}

