#include "libft/include/libft.h"
#include <readline/readline.h>
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
    if (!new_split)
        return ;
    i = 0;
    if (!split || !(split[i]))
        return ;
    while ((*split)[i])
    {
        new_split[i] = ft_strdup((*split)[i]);
        i++;
    }
    new_split[i] = NULL;
    free_split(*split);
    *split = new_split;
}

void add_split(char ***split, int *size, char *str)
{
    int k;

    k = *size;
    (*split)[k] = str;
    (*split)[++k] = NULL;
    my_realloc(split, k + 2);
    *size = k++;
}

char	*ft_strchr_valid(const char *s, int c) //se tiver o \ entao o que esta a frente vai ser ativado
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
		{
			if (s[i - 1] && s[i - 1] != '\\')
				return ((char *)&s[i]);
            else if (s[i - 1] && s[i - 2] && s[i - 2] == '\\')
                return ((char *)&s[i]);
		}
		i ++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_find_space(const char *s) //se tiver o \ entao o que esta a frente vai ser ativado
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			if (s[i - 1] && s[i - 1] != '\\')
				return ((char *)&s[i]);
		}
		i ++;
	}
	return (0);
}

int    check_quotes(char *str, char c, int *i)  //em caso de erro devolve -1
{
    char *aux;
    int j;

    j = *i;
    if (!str[j])
        return (-1);
    if (j > 0)
    {
        if (str[j - 1] && str[j - 1] == '\\')
        {
            ft_memmove(&str[j - 1], &str[j], ft_strlen(&str[j]) + 1);
            *i = j;
            return (0);
        }
    }
    if (str[j])
    {
        ft_memmove(&str[j], &str[j + 1], ft_strlen(&str[j + 1]) + 1);
        aux = ft_strchr_valid(&str[j], c);
        if (!aux)
            return (-1);
        *i += ft_strlen(&str[j]) - ft_strlen(aux);
        ft_memmove(aux, aux + 1, ft_strlen(aux));
    }
    else
        return (-1);
    return (0);
}

char *remove_slash(char *str)
{
    int i;
    char *aux;

    aux = ft_strdup(str);
    i = 0;
    while (aux[i])
    {
        if (aux[i] == '\\')
            if (!aux[i + 1] || (aux[i + 1] && aux[i + 1] != '\\'))
                ft_memmove(&aux[i], &aux[i + 1], ft_strlen(&aux[i + 1]) + 1);
        i++;
    }
    free(str);
    return (aux);
}

char    *algo(char *str)
{
    int i;
    char *aux;
    char c;

    i = 0;
    while (str[i])
    {
        while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i] != '\\')
            i++;
        if (!str[i] || ft_isspace(str[i]))
            return (remove_slash(ft_substr(str, 0, i)));
        else if (str[i] == '\\' && str[i + 1] && ft_isspace(str[i + 1]))
            ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
        else if (ft_isquote(str[i]))
        {
            if (check_quotes(str, str[i], &i) == -1)
                return (0);
            if (!str[i])
                return (ft_substr(str, 0, i));
            continue;
        }
        i++;
    }
    return (NULL);
}


char **split_command(char *str)
{
    int i;
    char    *aux;
    int     k;
    char    **split;

    k = 0;
    i = 0;
    split = malloc(sizeof(char*) * 2);
    split[0] = '\0';
    while (str[i])
    {
        aux = algo(&str[i]);
        if (!aux)
        {
            free_split(split);
            split = NULL;
            break ;
        }
        i += ft_strlen(aux);
        add_split(&split, &k, aux);
        if (!str[i])
            break;
        i++;
    }
    return (split);
}

int main()
{
    char *str;
    char **split;
    int i = 0;

    str = readline("line : ");
 	while (str != NULL)
	{
        add_history(str);
        split = split_command(str);
        // parse_split(split);
        if (split)
        {
            i = 0;
            while (split[i])
            {
                printf("%s\n", split[i]);
                i++;
            }
            free_split(split);
            free(str);
        }
		str = readline("line : ");
	}
    return (0);
}


/*
char **activate_slash(char *str)
{
    int i;
    int j;
    int k;
    char    **split;

    i = -1;
    j = 0;
    k = 0;
    if (!str || !str[i + 1])
        return (NULL);
    split = malloc(sizeof(char*) * 2);
    while (str[i + 1])
    {
        while (str[i + 1] && (!ft_isquote(str[++i]) && !ft_isspace(str[i]) && str[i] != '\\'));
        if (str[i] && ft_isquote(str[i]))
        {
            while (str[i + 1] && !ft_isquote(str[++i])) ;
            split[k] = ft_substr(str, j, i - j + 1);
            split[++k] = NULL;
            my_realloc(&split, k + 2);
            i++;
            j = i + 1;
        }
        else if (str[i] && ft_isspace(str[i]))
        {
            split[k] = ft_substr(str, j, i - j);
            split[++k] = NULL;
            my_realloc(&split, k + 2);
            j = i + 1;
            i++;
        }
        else
            i++;
    }
    split[k] = ft_substr(str, j, i - j);
    split[k + 1] = NULL;
    return (split);
}
*/