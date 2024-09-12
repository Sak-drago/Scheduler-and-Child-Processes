#include <stdlib.h>
#include <stdio.h>
#include <sys/sysinfo.h>

int main(){
  struct sysinfo info;
  long uptime;
  long h, m, s;

  if(sysinfo(&info) != 0){
    printf("Error: System info could not be fetched");
    return -1;
  }

  uptime = info.uptime;
  h = uptime/3600;
  m = (uptime%3600) / 60;
  s = uptime % 60;

  printf("Uptime: %ld hours, %ld minutes, %ld seconds\n", h,m,s);
  return 0;
}
