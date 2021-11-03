#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
  FILE *fp;
  int c, i, cnt=0, curPos = 0, stPos = 0, endPos=0;
  char *filelog;

  if (argc == 3){
    stPos = atoi(argv[1]);
    filelog = argv[2];
  }else{
    printf("Used: ./readlog stPos fileLog\n");
    return 0;
  }
  
  char sel[7];
  fp = fopen(filelog, "r");
  fseek(fp, 0, SEEK_END);
  endPos = ftell(fp);
  while (curPos < endPos){
    fseek(fp, curPos+stPos, SEEK_SET);
    curPos = ftell(fp);
    for (i = 0; i < 6; i++)
      sel[i] = getc(fp);

    sel[i] = '\0';
    if (strcmp(sel, "select") == 0|| strcmp(sel, "SELECT") == 0){
      fseek(fp, curPos, SEEK_SET);
      while (1){
        c = getc(fp);
        if (c == EOF)
          break;
        if (c == '\n'){
          char buf[cnt];
          fseek(fp, curPos, SEEK_SET);
          fread(&buf, cnt, 1, fp);
          buf[cnt] = '\0';
          printf("%s;\n", buf);
          curPos = ftell(fp)+1;
          cnt = 0;
          break;
        }
        cnt++;
      }
    }
  }
  fclose(fp);
  return 0;
}
