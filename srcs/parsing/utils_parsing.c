/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:50:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/07/29 19:50:37 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*checks if c is ' or "*/
int ft_isquote(char c)
{
    if (c == '\'' || c == '\"')
        return (1);
    return (0);
}

/*if the char c is found in string s, but is preceded by \, then its not valid */
char	*ft_strchr_valid(const char *s, int c) 
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

/*	reallocs split to have new size	*/
void	my_realloc(char ***split, int size)
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

/*	reallocs **split to size, size, increments it by one, and adds str as 
	the last element of **split */
void	add_split(char ***split, int *size, char *str)
{
	int k;

	k = *size;
	(*split)[k] = str;
	(*split)[++k] = NULL;
	my_realloc(split, k + 2);
	*size = k++;
}