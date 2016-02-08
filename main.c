#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
  int max = 255;
  int fp = open("pic.ppm", O_CREAT | O_WRONLY,0777);
  char out[16] = "P3 501 501 255 ";
  write(fp, out, 15);

  int grid[251][251];
  grid[0][0]=0;
  grid[0][1]=1;
  grid[0][2]=1;
  grid[1][0]=0;
  grid[1][2]=1;
  grid[2][0]=0;
  grid[2][1]=0;
  grid[2][2]=0;
  
  int i;
  for(i=3; i<=250; i++){
    int j;
    for(j=0; j<=i; j++){
      grid[i][j]=grid[i/3][j/3]+grid[i%3][j%3];
    }
  }
  
  for(i=-250; i<=250; i++){
    int j;
    for(j=-250; j<=250; j++){
      int r=0;
      int g=0;
      int b=0;
      if(i<=0) r=1;
      if(abs(i)>=abs(j)) b=1;
      if(j<=0) g=1;
      int x;
      if(b){
        x = 50*grid[abs(i)][abs(j)];
      }else{
        x = 50*grid[abs(j)][abs(i)];
      }
      sprintf(out, "%d %d %d \0", r*x, b*x, g*x);
      write(fp, out, strlen(out));
    }
  }
  close(fp);
  return 0;
}
