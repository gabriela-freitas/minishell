/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/07 01:54:56 by mfreixo-         ###   ########.fr       */
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
        while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i] != '\\')
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

void	second_parse(void)
{
	t_list	*temp;
	char	**split;
	int		i;

	i = 0;
	temp = base()->cmds;
	while (temp)
	{
		printf("line = %s\n", (char *) temp->content);
		split = split_command((char *)temp->content);
		execute(split);
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

/*

char **split_command(char *str)
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
    if (!split)
        return (NULL);
    while (str[i + 1])
    {
        while (str[i + 1] && (!ft_isquote(str[++i]) && !ft_isspace(str[i]) && str[i] != '\\'))
            ;
        if (str[i] && ft_isquote(str[i]))
        {
            while (str[i + 1] && !ft_isquote(str[++i])) ;
            if (str[i + 1] && !ft_isspace(str[i + 1]))
                continue;
            split[k] = ft_substr(str, j, i - j + 1);
            split[++k] = NULL;
            my_realloc(&split, k + 2);
            // i++;
            j = i++ + 2;
        }
        else if (str[i] && ft_isspace(str[i]))
        {
            split[k] = ft_substr(str, j, i - j);
            split[++k] = NULL;
            my_realloc(&split, k + 2);
            j = i + 1;
        }
        else if (str[i + 1] && ft_isquote(str[++i]))
            i++;
        if (!str[i])
            break ;
    }
    if (str[i])
    {
        split[k] = ft_substr(str, j, ft_strlen(&str[j]));
        split[k + 1] = NULL;
    } 
    return (split);
}
}*/