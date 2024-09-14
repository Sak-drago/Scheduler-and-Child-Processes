#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define NUM_P_MAX 100
#define MAX 100
#define false 0
#define true 1

typedef struct {
  int id;
  int arrival_time;
  int burst_time;
  int remaining_time;
  int response_time;
  int turnaround_time;
  int time_quantum;
} Process;

void bubble_sort(Process process[], int n);
void Fifo(Process process[], int n);
void Sjf(Process process[], int n);
void Srtf(Process process[], int n);
void Rr(Process process[], int n, int t_slice);

void bubble_sort(Process process[], int n) {
  int i, j;
  Process temp;

  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (process[j].arrival_time > process[j + 1].arrival_time || (process[j].arrival_time == process[j + 1].arrival_time && process[j].id > process[j + 1].id)) {
        temp = process[j];
        process[j] = process[j + 1];
        process[j + 1] = temp;
      }
    }
  }
}

void fifo_process(Process process[], int n, int response_time[], int turnaround_time[], int completion_time[]) {
  int sum, i, j, k;
  float total_turnaround_time = 0, total_response_time = 0;

  sum = process[0].arrival_time;
  for (j = 0; j < n; j++) {
    if (sum < process[j].arrival_time) {
      sum = process[j].arrival_time;
    }
    sum = sum + process[j].burst_time;
    completion_time[j] = sum;
  }

  /* Calculate Turn Around time */
  for (k = 0; k < n; k++) {
    turnaround_time[k] = completion_time[k] - process[k].arrival_time;
    total_turnaround_time = total_turnaround_time + turnaround_time[k];
  }

  /* Calculate Response time */
  for (k = 0; k < n; k++) {
    response_time[k] = turnaround_time[k] - process[k].burst_time;
    total_response_time = total_response_time + response_time[k];
  }

  printf("Order of execution: ");
  for (i = 0; i < n; i++) {
    printf("P%d ", process[i].id);
  }
  printf("\n");

  printf("Average Turnaround Time: %f\n", total_turnaround_time / n);
  printf("Average Response Time: %f\n", total_response_time / n);
}

void sjf(Process process[], int n, int response_time[], int turnaround_time[], int completion_time[]) {
  int sum, i, j, k;
  float total_turnaround_time = 0, total_response_time = 0;

  bubble_sort(process, n);

  sum = process[0].arrival_time;
  for (j = 0; j < n; j++) {
    if (sum < process[j].arrival_time) {
      sum = process[j].arrival_time;
    }
    sum = sum + process[j].burst_time;
    completion_time[j] = sum;
  }

  for (k = 0; k < n; k++) {
    turnaround_time[k] = completion_time[k] - process[k].arrival_time;
    total_turnaround_time = total_turnaround_time + turnaround_time[k];
  }

  for (k = 0; k < n; k++) {
    response_time[k] = turnaround_time[k] - process[k].burst_time;
    total_response_time = total_response_time + response_time[k];
  }

  printf("Order of execution: ");
  for (i = 0; i < n; i++) {
    printf("P%d ", process[i].id);
  }
  printf("\n");

  printf("Average Turnaround Time: %f\n", total_turnaround_time / n);
  printf("Average Response Time: %f\n", total_response_time / n);
}

void srtf(Process process[], int n, int response_time[], int turnaround_time[], int completion_time[]) {
  int i, j, k;
  float total_turnaround_time = 0, total_response_time = 0;
  int remaining_time[n];
  for (i = 0; i < n; i++) {
    remaining_time[i] = process[i].burst_time;
  }
  int current_time = 0;
  int done = 0;
  int shortest = 0;
  int min_remaining_time = INT_MAX;
  while (!done) {
    done = 1;
    for (i = 0; i < n; i++) {
      if (remaining_time[i] > 0) {
        done = 0;
        if (process[i].arrival_time <= current_time && remaining_time[i] < min_remaining_time) {
          shortest = i;
          min_remaining_time = remaining_time[i];
        }
      }
    }
    current_time++;
    remaining_time[shortest]--;
    min_remaining_time = INT_MAX;
    if (remaining_time[shortest] == 0) {
      completion_time[shortest] = current_time;
    }
  }

  /* Calculate Turn Around time */
  for (k = 0; k < n; k++) {
    turnaround_time[k] = completion_time[k] - process[k].arrival_time;
    total_turnaround_time = total_turnaround_time + turnaround_time[k];
  }

  /* Calculate Response time */
  for (k = 0; k < n; k++) {
    response_time[k] = turnaround_time[k] - process[k].burst_time;
    total_response_time = total_response_time + response_time[k];
  }

  printf("Order of execution: ");
  for (i = 0; i < n; i++) {
    printf("P%d ", process[i].id);
  }
  printf("\n");

  printf("Average Turnaround Time: %f\n", total_turnaround_time / n);
  printf("Average Response Time: %f\n", total_response_time / n);
}


void rr(Process process[], int n, int response_time[], int turnaround_time[], int completion_time[]) {
  int i, j, k;
  float total_turnaround_time = 0, total_response_time = 0;
  int sum = 0;
  sum = process[0].arrival_time;
  for (j = 0; j < n; j++) {
    if (sum < process[j].arrival_time) {
      sum = process[j].arrival_time;
    }
    sum = sum + process[j].burst_time;
    completion_time[j] = sum;
  }

  int remaining_time[n];
  for (int i = 0; i < n; i++) {
    remaining_time[i] = process[i].burst_time;
  }
  int current_time = 0;
  int done = false;
  while (!done) {
    done = true;
    for (int i = 0; i < n; i++) {
      if (remaining_time[i] > 0) {
        done = false;
      }
      if (remaining_time[i] > process[i].time_quantum) {
        current_time = current_time + process[i].time_quantum;
        remaining_time[i] = remaining_time[i] - process[i].time_quantum;
        printf("P%d ", process[i].id);
      } else {
        current_time = current_time + remaining_time[i];
        completion_time[i] = current_time;
        remaining_time[i] = 0;
        printf("P%d ", process[i].id);
      }
    }
  }
  printf("\n");

  /* Calculate Turn Around time */
  for (k = 0; k < n; k++) {
    turnaround_time[k] = completion_time[k] - process[k].arrival_time;
    total_turnaround_time = total_turnaround_time + turnaround_time[k];
  }

  /* Calculate Response time */
  for (k = 0; k < n; k++) {
    response_time[k] = turnaround_time[k] - process[k].burst_time;
    total_response_time = total_response_time + response_time[k];
  }

  printf("Average Turnaround Time: %f\n", total_turnaround_time / n);
  printf("Average Response Time: %f\n", total_response_time / n);
}

void Fifo(Process process[], int n) {
  int response_time[MAX], turnaround_time[MAX], completion_time[MAX];

  fifo_process(process, n, response_time, turnaround_time, completion_time);

  for (int i = 0; i < n; i++) {
    process[i].response_time = response_time[i];
    process[i].turnaround_time = turnaround_time[i];
  }
}

void Sjf(Process process[], int n) {
  int response_time[MAX], turnaround_time[MAX], completion_time[MAX];

  sjf(process, n, response_time, turnaround_time, completion_time);

  for (int i = 0; i < n; i++) {
    process[i].response_time = response_time[i];
    process[i].turnaround_time = turnaround_time[i];
  }
}

void Rr(Process process[], int n, int t_slice) {
  int response_time[MAX], turnaround_time[MAX], completion_time[MAX];

  // Set the time_quantum field for each process
  for (int i = 0; i < n; i++) {
    process[i].time_quantum = t_slice;
  }

  rr(process, n, response_time, turnaround_time, completion_time);

  for (int i = 0; i < n; i++) {
    process[i].response_time = response_time[i];
    process[i].turnaround_time = turnaround_time[i];
  }
}

void Srtf(Process process[], int n) {
  int response_time[MAX], turnaround_time[MAX], completion_time[MAX];

  srtf(process, n, response_time, turnaround_time, completion_time);

  for (int i = 0; i < n; i++) {
    process[i].response_time = response_time[i];
    process[i].turnaround_time = turnaround_time[i];
  }
}

int main() {
  int n, i, choice, t_slice;
  Process process[NUM_P_MAX];
  printf("Enter the number of Processes: \n");
  scanf("%d", &n);

  for (i = 0; i < n; i++) {
    printf("Enter the Arrival time and Burst time for process %d : \n", i + 1);
    scanf("%d %d", &process[i].arrival_time, &process[i].burst_time);
    process[i].id = i + 1;
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
  }

  printf("Enter the method of scheduling you wish to perform: \n");
  printf("1. FIFO\n");
  printf("2. SJF\n");
  printf("3. RR\n");
  printf("4. SRTF\n");
  scanf("%d", &choice);

  if (choice == 1) {
    Fifo(process, n);
  } else if (choice == 2) {
    Sjf(process, n);
  } else if (choice == 3) {
    printf("Enter the time slice for Round Robin: \n");
    scanf("%d", &t_slice);
    Rr(process, n, t_slice);
  } else if (choice == 4) {
    Srtf(process, n);
  } else {
    printf("Invalid choice.\n");
  }

  return 0;
}

