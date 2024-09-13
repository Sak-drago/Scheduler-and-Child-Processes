#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  pid_t pid;

  pid = fork();
  if(pid == 0){
    execlp("./date", "date", NULL);
  }

  pid = fork();
  if(pid == 0){
    execlp("./cal", "cal", "09", "2024", NULL);
  }

  pid = fork();
  if(pid == 0){
    execlp("./uptime", "uptime", NULL);
  }

  for(int i =0;i<3;i++) wait(NULL);
  return 0;
}
