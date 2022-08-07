/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/07 07:06:16 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expand variables from env
char	*find_env(char	*name)
{
	t_env	*aux;

	aux = base()->env_split;
	while (aux->next)
	{
		if (!ft_strncmp(name, aux->name, ft_strlen(name)))
			return (aux->content);
		aux = aux->next;
	}
	return (NULL);
}

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

void add_split(char ***split, int *size, char *str)
{
    int k;

    k = *size;
    (*split)[k] = str;
    (*split)[++k] = NULL;
    my_realloc(split, k + 2);
    *size = k++;
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
        ft_memmove(aux, aux + 1, ft_strlen(aux + 1) + 1);
    }
    else
        return (-1);
    return (0);
}

char    *algo(char *str)
{
    int i;
    char *aux;
    char c;

    i = 0;
    while (str[i])
    {
        while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i] != '\\' && str[i] != '$')
            i++;
        if (!str[i] || ft_isspace(str[i]))
            return (ft_substr(str, 0, i));
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

int is_expand(char c)
{
    if (c >= 34 && c <= 37)
        return (1);
    if (c >= 41 && c <= 47)
        return (1);
    if (c == 58 || c == 61 || c == 63 || c == 64)
        return (1);
    if (c == 91 || c == 93 || c == 93 || c == 94)
        return (1);
    if (c == 123 || c == 125 || c == 126)
        return (1);
    return (0);
}

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
            cmd = ft_strdup(find_env(aux3));
            free(aux3);
            if (cmd)
            {
                memmove(&(*str)[j], &(*str)[i], ft_strlen(&(*str)[i]) + 1);
                add_str(str, ft_strdup(cmd), j);
                i = j + ft_strlen(cmd);
                free(cmd);
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

char **split_command(char *str)
{
    int i;
    char    *aux;
    int     k;
    char    **split;

    k = 0;
    i = 0;
    printf("%s\n", str);
    expand_str(&str); //este expand nao esta a funcionar
    printf("%s\n", str);
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


void	second_parse(void)
{
	t_list	*temp;
	char	**split;
	int		i;

	i = 0;
	temp = base()->cmds;
	while (temp)
	{
		// printf("line = %s\n", (char *) temp->content);
		split = split_command((char *)temp->content);
		// execute(split);
		// i = 0;
		// while (split[i])
		// {
		// 	printf(">>%s<<\n", split[i]);
		// 	i++;
		// }
		// printf("----------\n");
		temp = temp->next;
		free_split(split);
	}
	ft_lstclear(&(base()->cmds), free);
}