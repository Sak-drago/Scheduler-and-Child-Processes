#include <stdio.h>
#include <stdlib.h>


int f_d(int m, int y){
  int q = 0; 
  int k = y%100;
  int j = y/100;

  if(m==1 || m==2){
    m+=12;
    y--;
    k = y%100;
    j = y/100;
  }

  int h = (q+(13*(m+1)/5)+k+(k/4)+(j/4)+(5*j))%7;
  return h;
}

int f_n_d(int  m, int y){
  int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  if(m == 2 && (y %4 == 0 && (y%100 != 0 || y%400 == 0))) return 29;
  return days_in_month[m-1];
}

int main(int argc,char* argv[]){
  if(argc !=3){
    printf("Error: Write all the arguements\n");
    return -1;
  }

  int m = atoi(argv[1]);
  int y = atoi(argv[2]);

  if(m>13 || m<1 || y<1){
    printf("Error: Not valid arguements\n");
    return -1;
  }

  int first = f_d(m,y);
  int days = f_n_d(m,y);
  printf("        %d\n", y);
  printf("Su Mo Tu We Th Fr Sa\n");

  for(int i = 0;i<first;i++){
    printf("  ");
  }

  for(int i =1;i<=days;i++){
    printf("%2d ",i);
    if((i+first)%7 == 0)printf("\n");
  }
  
  printf("\n");
  return 0;
}
