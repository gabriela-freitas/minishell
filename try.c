#include "libft/include/libft.h"
#include <readline/readline.h>
# include <readline/history.h>


void add_str(char **str, char *add, int pos)
{
    char *aux;
    char *aux2;

    aux = ft_substr(*str, pos, ft_strlen(&(*str)[pos]));
    ft_memmove(&(*str)[pos], add, ft_strlen(add) + 1);
    aux2 = malloc(sizeof(char) * (ft_strlen((*str)) + ft_strlen(aux) + 1));
    ft_memmove(aux2, (*str), ft_strlen((*str)) + 1);
    ft_memmove(aux2 + ft_strlen((*str)), aux, ft_strlen(aux) + 1);
    free(*str);
    *str = ft_strdup(aux2);
    free(aux);
    free(aux2);
}

void expand_str(char **str)
{
    int i;
    int j;
    char    *cmd;
    char    *aux3;

    j = 0;
    i = 0;
    while ((*str)[i])
    {
        if ((*str)[i] == '$')
        {
            j = i;
            while ((*str)[i] && !ft_isspace((*str)[i]))
                i++;
            aux3 = ft_substr((*str), j + 1, i - j - 1);
            if (!strcmp(aux3, "HOME"))
                cmd = ft_strdup("/mnt/c/mfreixo-");
            free(aux3);
            if (cmd)
            {
                memmove(&(*str)[j], &(*str)[i], ft_strlen(&(*str)[i]) + 1);
                add_str(str, ft_strdup(cmd), j);
                i = j + ft_strlen(cmd);
            }
            else
            {
                memmove(&(*str)[j], &(*str)[i], ft_strlen(&(*str)[i]) + 1);
                i = j + 1;
            }
        }
        i++;
    }
}

int main()
{
    char *str;

    str = ft_strdup("UM$HOME DOIS TRES");
    expand_str(&str);
    // add_str(&str, "dois", 2);
    printf("%s\n", str);
    return (0);
}

