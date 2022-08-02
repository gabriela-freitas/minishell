/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/02 23:26:13 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief deals with double quotes and quotes
 * expand env variables
 */

#include "minishell.h"

//if I find a valid pipe, I'm gonna split it already
	//update a variable >> pipe to true
//everything inside a "" is printed

void	first_parse(char *line)
{
	char	*temp;
	char	*str;
	char	*index;
	int		i;

	temp = malloc(sizeof(char) * (ft_strlen(line) + 1));
	i = -1;
	while (*line)
	{

	}
	temp[++i] = '\0';
	str = ft_strdup(temp);
	free(temp);
	printf("%s\n", str);
}

char	**double_quotes_pipes(char *str)
{
	int		i;
	char	**args;
	char	*temp;

	while (str)
	{
		if (*str == '\"')
		{
			ft_memmove(str, ++str, ft_strlen(str) + 1);
			str = ftstrchr(str, '\"');
			ft_memmove(str, ++str, ft_strlen(str) + 1);
		}
		if (*str == '|')
		{
			
		}
	}
	return (args));
}
