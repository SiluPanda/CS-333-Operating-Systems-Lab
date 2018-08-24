#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
head(int fd, int maximum_lines)
{
  int n;
  int curr_line = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0 && curr_line < maximum_lines) {
    for( int i = 0; i < n; i++){
      if(buf[i] == '\n'){
        curr_line++;
      }
      if(curr_line == maximum_lines){
        n = i+1;
        buf[n] = '\0';
        break;
      }
    }
    if (write(1, buf, n) != n) {
      printf(1, "head: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "head: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;
  int lines = atoi(argv[1]);
  if(argc <= 2){
    head(0, lines);
    exit();
  }

  for(i = 2; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "head: cannot open %s\n", argv[i]);
      exit();
    }
    head(fd, lines);
    close(fd);
  }
  exit();
}
