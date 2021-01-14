/*
		Author: Caraline Kneebone & Shane Combs
		Assignment Number: 2
		Date of Submission: 10/27/2020
		Name of this file: prime.c
		Description of the program: handles signals, finds next highest prime
*/
#include<stdio.h>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
#include<stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <math.h>
#include "main.h"

long unsigned int calculatedPrime;
long unsigned int starting_prime; 
int done_flag;
int p_number;
int priority;
unsigned int pid;


void checkPrimeAndPrint();//unsigned long int toCheck
int checkPrime(unsigned long int toCheck);
void handler(int signum, siginfo_t *info, void *ptr);
void suspend_p();
void resume_p();
void terminate_p();

void main(int argc, char *argv[]) {
	/* Install timer_handler as the signal handler for SIGALRM. */
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler;
	sigaction(SIGTERM, &sa, NULL);//signal terminated
	sigaction(SIGTSTP, &sa, NULL);//signal stopped
	sigaction(SIGCONT, &sa, NULL);//signal continue
	
	done_flag = NO;
	char* endptr;
	pid = getpid();
	p_number = atoi(argv[1]);
	priority = atoi(argv[2]);
	starting_prime = strtoul(argv[3], &endptr, 10);//convert string to long unsigned int
	calculatedPrime = starting_prime;
	checkPrimeAndPrint();

}

void handler(int signum, siginfo_t *info, void *ptr){
	if(signum == SIGTSTP){//if process is stopped
		suspend_p();
	}
	else if(signum == SIGCONT){//if process is running
		resume_p();
	}
	else if(signum == SIGTERM){//if process is terminated
		terminate_p();
	}
}

void suspend_p(){
	printf("Process %i: My priority is %i, my PID is %i: "
	"I am about to be suspended... "
	"Highest prime number I found is %lu\n",
	p_number, priority, pid, calculatedPrime);
	done_flag = YES;
}

void resume_p(){
	printf("Process %i: My priority is %i, my PID is %i: "
	"I just got resumed. Highest prime number I found is %lu\n",
	p_number, priority, pid, calculatedPrime);
	done_flag = NO;
}

void terminate_p(){
	printf("Process %i: My priority is %i, my PID is %i: "
	"I completed my "
	"task and I am exiting. Highest prime number I found is %lu\n",
	p_number, priority, pid, calculatedPrime);
	_exit(0);
}      

void checkPrimeAndPrint(){
	printf("Process %i: My priority is %i, my PID is %i: I just got started. I am starting "
		"with the number %lu to find the next prime number.\n", 
		p_number, priority, pid, starting_prime);
	
	int numPrinted = 0;
    long unsigned int numberToCheck = starting_prime +1; 
	
	while(1){

		while (done_flag == 1 && numPrinted <10) {
			if (checkPrime(numberToCheck) == 1){
				numPrinted++;
			}
			numberToCheck++;
		}
		while(done_flag == YES){  }
	}
	calculatedPrime = numberToCheck;
}

int checkPrime(unsigned long int toCheck){
      unsigned long int i = 2; 
      int prime = 1; 
      while (prime == 1&& i < toCheck/2){ 
              if (toCheck % i == 0) 
                prime = 0;
              i++;
      } 
      return (prime);
}