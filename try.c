#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

// ------------------------------------------------


int main (int argCount, char *argv[]) 
{
  char *str;
  HIST_ENTRY *histentry;
  HISTORY_STATE hist;
  
  hist.entries = malloc(sizeof(HIST_ENTRY*)*1000);
  while(str)
  {
    str = readline("prompt: ");
    add_history(str);
    free(str);
  }
  printf("%d\n", read(history_get(2)->timestamp));

  return (0);
}