#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


void utc();
void rfc();
void default_time();

int main(int argc, char *argv[]){
  if(argc == 1) default_time();
  else if(argc == 2){
    if(strcmp(argv[1], "-u")== 0){
      utc();
    }
    else if(strcmp(argv[1], "-r") == 0){
      //rfc();
    }
    else printf("Use either -u or -r\n");
  }
  
  else{
    printf("Too many arguements\n");
  }
  return 0;
}

void utc(){
  time_t t = time(NULL);
  struct tm tm = *gmtime(&t);
  printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year+1900,tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void default_time(){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year+1900,tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); 
}
