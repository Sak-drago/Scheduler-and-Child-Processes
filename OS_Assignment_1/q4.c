#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define NUM_P_MAX 100

typedef struct {
  int id;
  int arrival_time;
  int burst_time;
  int remaining_time;
  int response_time;
  int turnaround_time;
} Process;

void cal_t(Process process[], int n, int order[]);
void cal_avg(Process process[], int n, float *avg_r_t, float *avg_ta_t);
void Fifo(Process process[], int n);
void Sjf(Process process[], int n);
void Srtf(Process process[], int n);
void Rr(Process process[], int n, int t_slice);


void cal_t(Process process[], int n, int order[]){
  int curr_t = 0;
  int complete = 0;
  int pid;
  while(complete<n){
    int rem_t = INT_MAX;
    int min_i = -1;

    for(int i =0;i<n;i++){
      if(process[i].arrival_time<=curr_t && process[i].remaining_time < rem_t && process[i].remaining_time>0){
        rem_t = process[i].remaining_time;
        int min_i = i;
      }
    }
    if(min_i == -1){
      curr_t++;
      continue;
    }

    if(process[min_i].response_time == -1){
      process[min_i].response_time = curr_t - process[min_i].arrival_time;
    }

    process[min_i].remaining_time--;
    curr_t++;

    if(process[min_i].remaining_time == 0){
      complete++;
      process[min_i].turnaround_time = curr_t - process[min_i].arrival_time;
      order[complete-1] = process[min_i].id;
    }
  }
}

void cal_avg(Process process[], int n, float *avg_r_t, float *avg_ta_t){
  float tot_r_t = 0;
  float tot_ta_t = 0;

  for(int i = 0; i<n;i++){
    tot_r_t += process[i].response_time;
    tot_ta_t += process[i].turnaround_time;
  }

  *avg_r_t = tot_r_t/n;
  *avg_ta_t = tot_ta_t/n;
}


void Fifo(Process process[], int n){
  int order[n];
  float avg_r_t, avg_ta_t;

  for(int i = 0;i<n;i++){
    process[i].remaining_time = process[i].burst_time;
    process[i].response_time = -1;
  }

  printf("Check check");
  cal_t(process, n, order);
  cal_avg(process,n,&avg_r_t,&avg_ta_t);

  printf("FIFO order of Execution: ");
  for(int i = 0;i<n;i++){
    printf("%d ", order[i]);
  }

  printf("\n");
  printf("FIFO Average Response Time: %.2f\n", avg_r_t);
  printf("FIFO Average Turnaround Time: %.2f\n", avg_ta_t);
}

int main(){
  int n, i;
  Process process[NUM_P_MAX];
  printf("Enter the number of Processes: \n");
  scanf("%d", &n);


  for(i = 0;i<n;i++){
    printf("Enter the Arrival time and Burst time for process %d : \n",i+1);
    scanf("%d %d", &process[i].arrival_time, &process[i].burst_time);
    process[i].id = i+1;

    int c;
    while((c = getchar()) != '\n' && c!=EOF){}
  }

  printf("Check Check");
  for(int k = 0;k<n;k++){
    printf("%d : %d ", process[k].arrival_time, process[k].burst_time);
  }

  printf("Check Check");
  Fifo(process,n);
  return 0;
}
