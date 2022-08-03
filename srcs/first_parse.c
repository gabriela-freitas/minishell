/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:42:29 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/03 19:44:23 by gafreita         ###   ########.fr       */
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
	while(ft_isspace(str[++j]));
	ft_memmove((void *)str, (void *)&str[j], ft_strlen(&str[j]) + 1);
	i = -1;
	while (str[++i])
	{
		j = i;
		while(ft_isspace(str[j]) && str[j + 1] && ft_isspace(str[j + 1]))
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
	{
		if (*(str + 1) == '|')
		{
			return (0);
		}
	}
	return (1);
}

int	parse_pipe(char *str, char *begin)
{
	(void) begin;

	if (*(str + 1) == '|')
	{
		if (!check_pipes(str))
		{
			printf("parse error near `||'\n");
			return (0);
		}
			//create a new list;
	}
	else
	{
		if (!check_pipes(str))
		{
			printf("parse error near `|'\n");
			return (0);
		}
			//split to a new one
	}
	return (1);
}

char	**double_quotes_pipes(char *str)
{
	char	**args;
	char	*begin;

	args = malloc(sizeof(char *) * 2);
	begin = str;
	while (*str)
	{
		if (*str == '\"')
		{
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			str = ft_strchr(str, *str);
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		if (*str == '|')
			parse_pipe(str, begin);
	}
	return (1);
}

int	parse_pipe(char *str, char *begin)
{
	(void) begin;

	double_quotes_pipes(line);
	printf("%s\n", line);
}

