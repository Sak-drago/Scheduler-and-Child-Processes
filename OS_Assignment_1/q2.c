#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define ARRAY_SIZE 16

void bs(int arr[], int target, int l, int h){
  if(l>h){
      printf("-1\n");
      exit(0);
    }
  int mid = (h-l)/2 + l;

  if(arr[mid] == target){
    printf("Target : %d\n",mid);
  }
  
  else if(arr[mid] > target){
    pid_t pid = fork();
    if(pid == 0) bs(arr,target,l,mid-1);
    else wait(NULL);
  }
  else{
    pid_t pid = fork();
    if(pid == 0) bs(arr,target,mid+1,h);
    else wait(NULL);
  }
}
  
int main(){
  int arr[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  printf("Array : ");
  for(int i = 0;i<ARRAY_SIZE;i++) printf("%d ", arr[i]);
  printf("\n");

  int target;
  printf("Enter Target Value: ");
  scanf("%d", &target);
  bs(arr,target,0,ARRAY_SIZE-1);
}

