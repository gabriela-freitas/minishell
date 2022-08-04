/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/04 16:52:12 by gafreita         ###   ########.fr       */
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

//remove extra spaces outside " " and ' '
static void	remove_spaces(const char *str)
{
	size_t	i;
	size_t	j;
	char	*aux;

	j = -1;
	while (ft_isspace(str[++j]))
		;
	ft_memmove((void *)str, (void *)&str[j], ft_strlen(&str[j]) + 1);
	i = -1;
	while (str[++i])
	{
		j = i;
		while (ft_isspace(str[j]) && str[j + 1] && ft_isspace(str[j + 1]))
			j++;
		ft_memmove((void *)&str[i], (void *)&str[j], ft_strlen(&str[j]) + 1);
		if (str[i] == '\"' || str[i] == '\'')
		{
			aux = ft_strchr(&(str[i + 1]), str[i]);
			if (aux)
				i += (size_t)aux - (size_t)(&str[i]);
		}
	}
}

int	check_pipes(const char *str)
{
	while (ft_isspace(*(++str)))
		;
	if (*str == '|')
		return (0);
	return (1);
}

int	parse_pipe(char *str, char *begin)
{
	(void) begin;

	if (!check_pipes(str))
	{
		printf("parse error near `|'\n");
		return (0);
	}
	printf("found a valid pipe!\n");
		//create a new list
	return (1);
}

char	**search_pipes(char *str)
{
	char	**args;
	char	*begin;

	args = malloc(sizeof(char *) * 2);
	begin = str;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			str = ft_strchr(str + 1, *str);
		if (*str == '|')
			parse_pipe(str, begin);
		str++;
	}
	return (args);
}

void	first_parse(char *line)
{
	remove_spaces(line);
	search_pipes(line);
	printf("%s\n", line);
}
