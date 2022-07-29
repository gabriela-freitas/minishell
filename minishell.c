#include <stdio.h>
#include "./get_next_line/get_next_line.h"
#include <signal.h>
#include  <stdlib.h>
#include <unistd.h>
void     INThandler(int);

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("\n");
     signal(SIGINT, INThandler);
     write(1, "mini$: ", 7);
}

void read_loop()
{
    char *str;

    while (str != NULL)
    {
        write(1, "mini$: ", 7);
        signal(SIGINT, INThandler);
        str = get_next_line(0);
    }
    printf("\n");
}

int main()
{
     char *str;
     int size;
     
 //    str = get_next_line(0);
 //    if (str)
  //        printf("%s\n", str);
     read_loop();
     return (0);
}
