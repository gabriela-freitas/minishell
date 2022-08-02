#include "minishell.h"

int ft_issapce(char c)
{
    if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == ' ')
        return (1);
    else
        return (0);
}

int ft_isBuiltIn(char *cmd)
{
    printf("cmd = %s\n", cmd);
    if (ft_strncmp(cmd, "echo", 5))
        return (ECHO);
    if (ft_strncmp(cmd, "cd", 2))
    {
        printf("cmd = %s\n", cmd);
        return (CD);
    }
    if (ft_strncmp(cmd, "pwd", 4))
        return (PWD);
    if (ft_strncmp(cmd, "env", 4))
        return (ENV);
    if (ft_strncmp(cmd, "export", 7))
        return (EXPORT);
    if (ft_strncmp(cmd, "exit", 6))
        return (EXIT);
    if (ft_strncmp(cmd, "unset", 6))
        return (UNSET);
    return (-1);
}

int check_cmd(char *str)
{
    printf("%d\n", ft_isBuiltIn(str));
    return (0);
}


void parser(char *str)
{
    char *args;
    char *cmd;
    int i;
    size_t length;

    if (!str)
        return ;
    length = ft_strlen(str);
    while (*str && ft_issapce(*str) == 1)
        str++;
    i = 0;
    while (str[i] && ft_issapce(str[i++]) == 0);
    cmd = ft_substr(str, 0, i); //criar saida para erro do cmd
 //   check_cmd(cmd);
    while (str[i] && ft_issapce(str[++i]) == 1);
    args = ft_substr(str, i, length); //criar saida para erro do cmd
    printf("cmd = %s\n", cmd);
    printf("args = %s\n", args);
    free(cmd); //nao libertar se der erro
    free(args); // nao libertar se der erro
    return ;
}

