#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>


int random_n(){
	return rand()%100+1; //Generating a random number between 1 and INT_MAX and modulo it by 100
}

int mean_cal(){
	int number[4];
	int total=0;
	for(int i = 0;i<4;i++){
		number[i] = random_n();
		total+=number[i];
		}
	return total/4;
}

int main(void){
	for(int i = 0;i<7;i++){
		pid_t pid = fork();

		if(pid<0){
		printf("Error\n");
		exit(EXIT_FAILURE);
		}

		else if(pid == 0){
		srand((unsigned int)time(NULL)+getpid()); //Avoids compiler warning
		int mean_n = mean_cal();
		printf("Mean: %i\n", mean_n);
		exit(EXIT_SUCCESS);
		}
	}
	for(int i = 0;i<7;i++){
		wait(NULL);
	}
	return 0;
}

