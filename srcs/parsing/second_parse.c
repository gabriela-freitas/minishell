/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/06 20:29:07 by mfreixo-         ###   ########.fr       */
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

void activate_slash(char *str) //fazer um activate quotes
{
    int i;
	char *aux;

    i = 0;
	aux = str;
    while (*str)
    {
		if (*str == '\"')
		{
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			str = ft_strchr(str, '\"');
			if (*str)
				ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		str++;
    }
	str = aux;
	while (*str)
    {
		if (*str == '\\')
            ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		str++;
    }
    
}

void parse_split(char **split)
{
    int i;
    
    i = 0;
    while (split[i])
    {
        activate_slash(split[i]);
        i++;
    }
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

char *algo(char *str)
{
    int i;
    char *aux;

    i = 0;
    if (ft_isquote(*str))
    {
        aux = ft_strchr_valid(str + 1, *str);
        if (*aux && *(aux + 1) && !ft_isspace(*(aux + 1)))
            return (algo(aux));
        else
            return (aux);
    }
    else
    {
        aux = ft_find_space(str); 
        if (aux)
            return (aux + 1);
    }
    return (0);
}

char **split_command(char *str)
{
    int i;
    char *aux;
    char **split;
    int k;

    i = 0;
    split = malloc(sizeof(char*) * 2);
    split[0] = '\0';
    k = 0;
    while (str && *str)
    {
        aux = algo(str);
        if (ft_isquote(*str))
        {
            printf("%s\n", ft_substr(str, 1, aux - str - 1));
            str = aux + 2;
        }
        else
        {
            printf("%s\n", ft_substr(str, 0, aux - str));
            str = aux + 1;
        }
        if (!aux)
            break ;
    }
}

/*
void add_split(char ***split, int *size, char *str)
{
    int k;

    k = *size;
    (*split)[k] = str;
    (*split)[++k] = NULL;
    my_realloc(split, k + 2);
    *size = k++;
}

int split_cmd_aux(char ***split, char *str, int *i, int *j)
{
    static int k;
    int i_aux;

    if (split && *split && !((*split)[0]))
        k = 0;
    i_aux = *i;
    if (str[i_aux] && ft_isquote(str[i_aux]))
    {
        while (str[i_aux + 1] && !ft_isquote(str[++i_aux])) ;
        if (str[i_aux + 1] && !ft_isspace(str[i_aux + 1]))
        {
            *i = i_aux;
            return (-1);
        }
        add_split(split, &k, ft_substr(str, *j, i_aux - *j + 1));
        *j = i_aux++ + 2;
    }
    else if (str[i_aux] && ft_isspace(str[i_aux]))
    {
        add_split(split, &k, ft_substr(str, *j, i_aux - *j // +1));
        *j = i_aux + 1;
    }
    else if (str[i_aux + 1] && ft_isquote(str[++i_aux]))
        i_aux++;
    *i = i_aux;
    return (k);
}

// void add_split(char **split, int size)
char **split_command(char *str)
{
    int i;
    int j;
    int k;
    char    **split;

    i = -1;
    j = 0;
    k = 0;
    split = malloc(sizeof(char*) * 2);
    if (!split)
        return (NULL);
    split[0] = '\0';
    while (str[i + 1])
    {
        while (str[i + 1] && (!ft_isquote(str[++i]) && !ft_isspace(str[i]) && str[i] != '\\'))
            ;
        k = split_cmd_aux(&split, str, &i, &j);
        if (k == -1)
            continue;
        if (!str[i])
            break ;
    }
    if (str[i])
        add_split(&split, &k, ft_substr(str, j, ft_strlen(&str[j])));
    return (split);
}
*/

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
		// parse_split(split);
		// execute(split);
		i = 0;
		while (split[i])
		{
			printf(">>%s<<\n", split[i]);
			i++;
		}
		printf("----------\n");
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