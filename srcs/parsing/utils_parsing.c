/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/02 10:31:05 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*checks if c is ' or "*/
int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

/*	reallocs split to have new size	*/
static void	my_realloc(char ***split, int size)
{
	char	**new_split;
	int		i;

	new_split = malloc(sizeof(char *) * size);
	if (!new_split)
		return ;
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

/*	reallocs **split to size, size, increments it by one, and adds str as
	the last element of **split */
void	add_split(char ***split, int *size, char *str)
{
	int	k;

	k = *size;
	(*split)[k] = str;
	(*split)[++k] = NULL;
	my_realloc(split, k + 2);
	*size = k++;
}

int	ft_redirec(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_redirec(char *str, int i)
{
	while(str[i] && ft_redirec(str[i]))
		i++;
	return (i);
}
