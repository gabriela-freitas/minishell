/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/06 10:38:58 by mfreixo-         ###   ########.fr       */
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

char	**split_command(char	*cmd)
{
    char    **split;
    int     i;
    int     j;
    int     k;

	// if (ft_strchr(cmd, '\"')) //entra aqui se nao tiver aspas
	// 	return (ft_split(cmd, ' '));
 	i = 0;
    j = 0;
    k = 0;
    split = malloc(sizeof(char*) * 2);
    while (cmd[i])
    {
        if (ft_isquote(cmd[i]))
            while (!ft_isquote(cmd[++i])) ;
        if (ft_isspace(cmd[i]))
        {
            split[k] = ft_substr(cmd, j, i - j);
            split[++k] = NULL;
            my_realloc(&split, k + 2);
            j = i + 1;
        }
        i++;
    }
    split[k] = ft_substr(cmd, j, i - j);
    split[k + 1] = NULL;
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
		split = split_command((char *)temp->content);
		while (split[i])
		{
			printf(">>%s\n", split[i]);
			i++;
		}
		printf("----------\n");
		temp = temp->next;
	}
	free_split(split);
}