# include <stdio.h>
# include "libft/include/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int main()
{
    char *str;

    str = readline("");
    while (*str)
    {
        printf("%c\n", *str);
        str++;
    }
    return (0);
}