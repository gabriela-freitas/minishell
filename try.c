#include "libft/include/libft.h"
#include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int ft_isquote(char c)
{
    if (c == '\'' || c == '\"')
        return (1);
    return (0);
}

void my_realloc(char ***split, int size)
{
    char    **new_split;
    int     i;

    new_split = malloc(sizeof(char*) * size);
    i = 0;
    while ((*split)[i])
    {
        new_split[i] = ft_strdup((*split)[i]);
        i++;
    }
    new_split[i] = NULL;
    free_split(*split);
    *split = new_split;
}


char **split_command(char *str)
{
    char    **split;
    int     i;
    int     j;
    int     k;
    char    *cmd;

    i = 0;
    j = 0;
    k = 0;
    split = malloc(sizeof(char*) * 2);
    while (str[i])
    {
        if (ft_isquote(str[i]))
            while (!ft_isquote(str[++i])) ;
        if (ft_isspace(str[i]))
        {
            split[k] = ft_substr(str, j, i - j);
            split[++k] = NULL;
            my_realloc(&split, k + 2);
            j = i + 1;
        }
        i++;
    }
    split[k] = ft_substr(str, j, i - j);
    split[k + 1] = NULL;
    return (split);
}


int main()
{
	char	*str;
    char **split;
    int     i;

    split = NULL;
	str = readline("minishell$: ");
    split = split_command(str);
    free(str);
    free_split(split);
    return (0);
}